import sign from "./sign";
import jsonToUrlEncoded from "@utils/jsonToUrlEncoded";

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
    return data.result.songs[0];
}