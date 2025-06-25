import type { SongResponse } from "./player.d";

/**
 * 获取指定歌曲的播放信息。
 *
 * @param id - 歌曲的唯一标识符。
 * @param level - 音质等级，默认为 "jyeffect"。
 * @returns 一个 Promise，解析为 SongResponse 类型的结果。
 */
export default async function getSong(id: number, level: string = "jyeffect"): Promise<SongResponse> {
    const url = `https://interface.music.163.com/api/song/enhance/player/url/v1`;

    const data = new URLSearchParams();
    data.append("ids", JSON.stringify([id]));
    data.append("level", level);
    data.append("immerseType", "c51");
    data.append("encodeType", "aac");
    data.append("trialMode", "-1");
    data.append("e_r", "true");

    const response = await fetch(url, {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:134.0) Gecko/20100101 Firefox/134.0",
            "Origin": "orpheus://orpheus",
            "Sec-Ch-Ua": '"Chromium";v="91"',
            "Sec-Ch-Ua-Mobile": "?0",
            "Sec-Fetch-Site": "cross-site",
            "Sec-Fetch-Mode": "cors",
            "Sec-Fetch-Dest": "empty",
            "Accept-Language": "en-US,en;q=0.9",
            "Cookie": "这里是Cookie,后续再加配置吧（"
        },
        body: data
    });

    return await response.json() as SongResponse;
}