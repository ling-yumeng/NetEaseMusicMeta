// 定义返回数据的类型
interface FreeTrialPrivilege {
    resConsumable: boolean; // 资源是否可消耗
    userConsumable: boolean; // 用户是否可消耗
    listenType: string | null; // 听歌类型，可能为空
    cannotListenReason: string | null; // 无法听歌的原因，可能为空
    playReason: string | null; // 播放原因，可能为空
    freeLimitTagType: string | null; // 免费限制标记类型，可能为空
}

interface FreeTimeTrialPrivilege {
    resConsumable: boolean; // 资源是否可消耗
    userConsumable: boolean; // 用户是否可消耗
    type: number; // 类型
    remainTime: number; // 剩余时间
}

interface SongData {
    id: number; // 歌曲ID
    url: string; // 歌曲链接
    br: number; // 音质比特率
    size: number; // 歌曲大小（字节）
    md5: string; // 歌曲的MD5值
    code: number; // 返回码
    expi: number; // 过期时间
    type: string; // 文件类型
    gain: number; // 增益值
    peak: number; // 峰值
    closedGain: number; // 关闭增益
    closedPeak: number; // 关闭峰值
    fee: number; // 费用
    uf: string | null; // 用户信息，可能为空
    payed: number; // 是否已支付
    flag: number; // 标记
    canExtend: boolean; // 是否可以扩展
    freeTrialInfo: string | null; // 免费试用信息，可能为空
    level: string; // 质量等级
    encodeType: string; // 编码类型
    channelLayout: string | null; // 声道布局，可能为空
    freeTrialPrivilege: FreeTrialPrivilege; // 免费试用特权
    freeTimeTrialPrivilege: FreeTimeTrialPrivilege; // 免费时长特权
    urlSource: number; // 来源
    rightSource: number; // 权利来源
    podcastCtrp: string | null; // 播客控制，可能为空
    effectTypes: string | null; // 效果类型，可能为空
    time: number; // 歌曲时长（秒）
    message: string | null; // 消息，可能为空
    levelConfuse: string | null; // 级别混淆，可能为空
    musicId: string; // 音乐ID
    accompany: string | null; // 是否伴奏，可能为空
    sr: number; // 采样率
    auEff: string | null; // 音频效果，可能为空
}

// 定义整体响应的类型
interface SongResponse {
    data: SongData[]; // 包含歌曲数据的数组
    code: number; // 返回码
}

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

    const res = await response.json() as SongResponse;
    return res;
}