import sign from "./sign.js";
import { URLSearchParams } from "url";

interface LyricResponse {
    code: number;
    lrc: {
        lyric: string;
    };
};

/**
 * 获取网易云歌词
 * @param id 歌曲 ID
 */
export default async function getLyric(id: number): Promise<string> {
    const payload = {
        id: String(id),
        lv: -1,
        tv: -1,
        csrf_token: ""
    };

    const { encText, encSecKey } = await sign(payload);

    const body = new URLSearchParams({
        params: encText,
        encSecKey
    });

    const response = await fetch("https://music.163.com/weapi/song/lyric", {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded",
        },
        body
    });

    if (!response.ok) {
        throw new Error(`请求失败: ${response.status}`);
    }

    const result = await response.json() as LyricResponse

    if (result?.lrc?.lyric) {
        return result.lrc.lyric;
    }

    return "";
}
