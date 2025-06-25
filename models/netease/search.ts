import sign from "./sign";
import jsonToUrlEncoded from "@utils/jsonToUrlEncoded";
import type { Song } from "./search.d";
/**
 * 根据关键词在网易云音乐进行搜索，返回搜索结果中的第一首歌曲信息
 * @param keywords - 搜索关键词
 * @returns 搜索结果中的第一首歌曲信息
 */
export default async function search(keywords: string) {
    let e = {
        "s": String(keywords),
        "limit": "1",
        "csrf_token": ""
    }

    const { encText, encSecKey } = await sign(e);

    const body = jsonToUrlEncoded({
        params: encText,
        encSecKey
    });

    const response = await fetch("https://music.163.com/weapi/search/suggest/web?csrf_token=", {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded",
        },
        body,
    });

    if (!response.ok) {
        throw new Error(`请求失败: ${response.status} ${response.statusText}`);
    }

    const data = await response.json() as any
    return data.result.songs[0] as Song;
}