export interface Detail {
    id: number;                 // 歌曲 ID
    name: string;              // 歌曲名称
    cover: string;             // 歌曲封面
    artists: string[];         // 歌手列表
    album: {
        id: number;             // 专辑 ID
        name: string;           // 专辑名称
    };
    duration: number;          // 歌曲时长（毫秒）
    bitrate: number;           // 最大码率
    publishTime: number;       // 发布时间（时间戳）
    mvId: number | null;       // MV ID
}