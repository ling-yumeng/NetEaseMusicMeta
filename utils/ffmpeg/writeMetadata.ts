import fs from 'fs/promises';
import path from 'path';
import { execFile } from 'child_process';
import { pipeline } from 'stream/promises';
import { createWriteStream } from 'fs';
import type { Detail } from '../../types/Detail';

/**
 * 下载资源文件并保存到本地路径
 */
async function downloadFile(url: string, destPath: string): Promise<void> {
    try {
        const res = await fetch(url);
        if (!res.ok || !res.body) throw new Error(`下载失败: ${url}`);
        await pipeline(res.body as any, createWriteStream(destPath));
    } catch (error) {
        throw new Error(`下载封面图片失败: ${error instanceof Error ? error.message : String(error)}`);
    }
}

/**
 * 转义特殊字符，防止FFmpeg参数解析错误
 */
function escapeMetadata(text: string): string {
    return text
        .replace(/\\/g, '\\\\')
        .replace(/"/g, '\\"')
        .replace(/'/g, "\\'")
        .replace(/\n/g, '\\n')
        .replace(/\r/g, '\\r')
        .replace(/\t/g, '\\t')
}

/**
 * 创建歌词文件（LRC格式），提高播放器兼容性
 */
async function createLyricsFile(filePath: string, lyric: string): Promise<string | null> {
    if (!lyric.trim()) return null;

    const lrcPath = filePath.replace(path.extname(filePath), '.lrc');

    try {
        // 如果歌词不是LRC格式，则创建简单的LRC格式
        let lrcContent = lyric;
        if (!lyric.includes('[') || !lyric.includes(']')) {
            const lines = lyric.split('\n').filter(line => line.trim());
            lrcContent = lines.map((line, index) => {
                const minutes = Math.floor(index * 5 / 60);
                const seconds = (index * 5) % 60;
                return `[${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}.00]${line}`;
            }).join('\n');
        }

        await fs.writeFile(lrcPath, lrcContent, 'utf-8');
        return lrcPath;
    } catch (error) {
        console.warn('创建歌词文件失败:', error);
        return null;
    }
}

/**
 * 获取文件格式特定的元数据参数
 */
function getFormatSpecificArgs(ext: string, detail: Detail, lyric: string): string[] {
    const escapedLyric = escapeMetadata(lyric);
    const commonMetadata = [
        '-metadata', `title=${escapeMetadata(detail.name)}`,
        '-metadata', `artist=${escapeMetadata(detail.artists.join('/'))}`,
        '-metadata', `album=${escapeMetadata(detail.album.name)}`,
        '-metadata', `date=${new Date(detail.publishTime).getFullYear()}`,
        '-metadata', `comment=${escapeMetadata(`ID:${detail.id} MV:${detail.mvId ?? '无'}`)}`,
    ];

    switch (ext.toLowerCase()) {
        case 'mp3':
            return [
                ...commonMetadata,
                '-id3v2_version', '3',
                '-metadata', `USLT=${escapedLyric}`,  // 使用USLT标签存储歌词
                '-metadata', `lyrics=${escapedLyric}`, // 兼容性备用
            ];

        case 'flac':
            return [
                ...commonMetadata,
                '-metadata', `LYRICS=${escapedLyric}`,
                '-metadata', `UNSYNCEDLYRICS=${escapedLyric}`,
            ];

        case 'm4a':
        case 'mp4':
            return [
                ...commonMetadata,
                '-metadata', `lyrics=${escapedLyric}`,
                '-metadata', `©lyr=${escapedLyric}`,  // iTunes格式
            ];

        case 'ogg':
        case 'oga':
            return [
                ...commonMetadata,
                '-metadata', `LYRICS=${escapedLyric}`,
                '-metadata', `UNSYNCEDLYRICS=${escapedLyric}`,
            ];

        default:
            return [
                ...commonMetadata,
                '-metadata', `lyrics=${escapedLyric}`,
            ];
    }
}

/**
 * 将歌曲元信息和歌词写入音频文件（覆盖原文件）
 */
export default async function writeMetadataWithFFmpeg(
    filePath: string,
    detail: Detail,
    lyric: string
) {
    const ext = path.extname(filePath).slice(1);
    const tempOut = `${filePath}.tmp.${ext}`;
    const coverPath = `${filePath}.cover.jpg`;
    let lrcPath: string | null = null;

    try {
        await fs.access(filePath);
        await downloadFile(detail.cover, coverPath);
        lrcPath = await createLyricsFile(filePath, lyric);
        const formatArgs = getFormatSpecificArgs(ext, detail, lyric);

        const args = [
            '-y',  // 覆盖输出文件
            '-i', filePath,
            '-i', coverPath,
            '-map', '0:a',  // 映射音频流
            '-map', '1:0',  // 映射封面图片
            '-c:a', 'copy', // 复制音频流，不重新编码
            '-c:v', 'copy', // 复制视频流（封面）
            ...formatArgs,
            '-metadata:s:v:0', 'title=Album cover',
            '-metadata:s:v:0', 'comment=Cover (front)',
            '-disposition:v:0', 'attached_pic',  // 标记为附加图片
            tempOut
        ];

        await new Promise<void>((resolve, reject) => {
            const ffmpeg = execFile('ffmpeg', args, async (err, stdout, stderr) => {
                if (err) {
                    console.error('FFmpeg 错误输出：', stderr);
                    console.error('FFmpeg 标准输出：', stdout);
                    return reject(new Error(`FFmpeg执行失败: ${stderr || err.message}`));
                }
                resolve();
            });

            const timeout = setTimeout(() => {
                ffmpeg.kill('SIGTERM');
                reject(new Error('FFmpeg执行超时'));
            }, 30000);

            ffmpeg.on('exit', () => {
                clearTimeout(timeout);
            });
        });

        await fs.rename(tempOut, filePath);
    } catch (error) {
        await Promise.allSettled([
            fs.unlink(tempOut).catch(() => { }),
        ]);

        throw new Error(`写入元数据失败: ${error instanceof Error ? error.message : String(error)}`);
    } finally {
        await Promise.allSettled([
            fs.unlink(coverPath).catch(() => { }),
        ]);
    }
}