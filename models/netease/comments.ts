import sign from "./sign.js";
import jsonToUrlEncoded from "@utils/jsonToUrlEncoded";
import type { ResponseData } from './comments.d';

/**
 * 获取网易云音乐评论数据
 *
 * @param id - 歌曲ID，用于构建评论请求参数
 * @returns 返回解析后的评论数据Promise对象，包含评论列表和其他相关信息
 * @throws 如果HTTP请求失败，会抛出包含状态码和状态文本的错误
 */
export default async function getComments(id: number) {
    let payload = {
        "rid": `R_SO_4_${id}`,
        "threadId": `R_SO_4_${id}`,
        "pageNo": 1,
        "pageSize": 20,
        "cursor": -1,
        "offset": 0,
        "orderType": 1
    }
    const { encText, encSecKey } = await sign(payload);
    const body = jsonToUrlEncoded({
        params: encText,
        encSecKey
    });

    const response = await fetch(`https://music.163.com/weapi/comment/resource/comments/get?csrf_token=`, {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded"
        },
        body
    });

    if (!response.ok) {
        throw new Error(`请求失败: ${response.status} ${response.statusText}`);
    }

    return await response.json() as ResponseData;
}