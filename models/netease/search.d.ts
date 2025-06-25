// 歌曲信息
export interface Song {
    id: number; // 歌曲 ID
    name: string; // 歌曲名称
    artists: Artist[]; // 歌手列表
    album: Album; // 专辑信息
    duration: number; // 歌曲时长
    copyrightId: number; // 版权 ID
    status: number; // 状态
    alias: string[]; // 别名
    rtype: number; // 类型
    ftype: number; // 类型
    mvid: number; // MV ID
    fee: number; // 费用
    rUrl: string | null; // 音源 URL
    mark: number; // 标记
}

// 歌手信息
interface Artist {
    id: number; // 歌手 ID
    name: string; // 歌手名称
    picUrl: string | null; // 歌手图片 URL
    alias: string[]; // 别名
    albumSize: number; // 专辑数量
    picId: number; // 图片 ID
    fansGroup: null; // 粉丝团
    img1v1Url: string; // 1v1 图片 URL
    img1v1: number; // 1v1 图片 ID
    trans: string | null; // 转换
}

// 专辑信息
interface Album {
    id: number; // 专辑 ID
    name: string; // 专辑名称
    artist: Artist; // 歌手信息
    publishTime: number; // 发行时间
    size: number; // 专辑大小
    copyrightId: number; // 版权 ID
    status: number; // 状态
    picId: number; // 图片 ID
    mark: number; // 标记
}