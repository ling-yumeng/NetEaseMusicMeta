import sign from "./sign";
import jsonToUrlEncoded from "@utils/jsonToUrlEncoded";
import type { Detail } from "../../types/Detail";
/**
 * 获取网易云歌曲原始详情
 * @param id 歌曲 ID
 */
export default async function getDetail(id: number): Promise<Detail | null> {

    const payload = {
        id,
        c: JSON.stringify([{ id }])
    };

    const { encText, encSecKey } = await sign(payload);

    const body = jsonToUrlEncoded({
        params: encText,
        encSecKey
    });

    const response = await fetch(`https://music.163.com/weapi/v3/song/detail`, {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded",
            "Cookie": "NMTID=00OxTqBQOEobT0EzElhoybqM9hFjBQAAAGXcKWzwQ"
        },
        body
    });

    if (!response.ok) {
        throw new Error(`请求失败: ${response.status} ${response.statusText}`);
    }

    return formatSongDetail(await response.json());
}

/**
 * 格式化网易云歌曲详情结构
 * @param raw 原始 API 返回数据
 */
function formatSongDetail(raw: any): Detail | null {
    const song = raw?.songs?.[0];

    if (!song) return null;

    return {
        id: song.id,
        name: song.name,
        artists: song.ar.map((a: any) => a.name),

        album: {
            id: song.al.id,
            name: song.al.name,
            cover: song.al.picUrl
        },

        cover: song.al.picUrl,

        duration: song.dt,
        bitrate: song.h?.br || song.m?.br || song.l?.br || 0,
        publishTime: song.publishTime,
        mvId: song.mv || null,
    };
}
