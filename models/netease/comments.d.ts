// 响应数据类型
export interface ResponseData {
    code: number; // 响应状态码
    data: CommentData; // 评论数据
    message: string; // 消息
}

// 评论数据类型
interface CommentData {
    commentsTitle: string; // 评论标题
    comments: Comment[]; // 评论列表
    currentCommentTitle: string; // 当前评论标题
    currentComment: null; // 当前评论
    totalCount: number; // 总评论数
    hasMore: boolean; // 是否还有更多
    cursor: string; // 时间游标
    sortType: number; // 排序类型
    sortTypeList: SortType[]; // 排序类型列表
    style: string; // 样式
    bottomAction: null; // 底部操作
    likeAnimation: null; // 点赞动画
    newReplyExpGroupName: null; // 新回复实验组名称
    expandCount: number; // 展开数量
    orderType: null; // 订单类型
    hotComments: HotComment[]; // 热门评论
}

// 排序类型
interface SortType {
    sortType: number; // 排序类型
    sortTypeName: string; // 排序类型名称
    target: string; // 目标
}

// 热门评论
interface HotComment {
    user: User; // 用户信息
    beReplied: BeReplied[] | null; // 被回复信息
    commentId: number; // 评论 ID
    threadId: string; // 评论线程 ID
    content: string; // 评论内容
    richContent: string | null; // 富文本内容
    status: number; // 状态
    time: number; // 时间戳
    timeStr: string; // 时间字符串
    needDisplayTime: boolean; // 是否需要显示时间
    likedCount: number; // 点赞数
    replyCount: number; // 回复数
    liked: boolean; // 是否点赞
    expressionUrl: string | null; // 表情图片 URL
    parentCommentId: number; // 父评论 ID
    repliedMark: boolean; // 是否已回复
    pendantData: PendantData | null; // 挂件数据
    pickInfo: null; // 精选信息
    showFloorComment: ShowFloorComment; // 显示楼中楼评论
    decoration: Decoration; // 装饰信息
    commentLocationType: number; // 评论位置类型
    musicianSayAirborne: null; // 音乐家说空中
    args: null; // 参数
    tag: Tag; // 标签
    source: null; // 来源
    resourceSpecialType: null; // 资源特殊类型
    extInfo: ExtInfo; // 扩展信息
    commentVideoVO: CommentVideoVO; // 评论视频信息
    contentResource: ContentResource | null; // 内容资源
    contentPicNosKey: string | null; // 内容图片 NOS Key
    contentPicExt: string | null; // 内容图片扩展名
    contentPicUrl: string | null; // 内容图片 URL
    grade: string | null; // 等级
    userBizLevels: null; // 用户业务等级
    userNameplates: null; // 用户名牌
    ipLocation: IPLocation; // IP 位置
    owner: boolean; // 是否是主人
    tail: null; // 尾部信息
    hideSerialComments: null; // 是否隐藏连续评论
    hideSerialTips: null; // 是否隐藏连续评论提示
    topicList: null; // 话题列表
    privacy: number; // 隐私设置
    medal: null; // 勋章
    outShowComments: OutShowComment[]; // 外部显示评论
    likeAnimationMap: LikeAnimationMap; // 点赞动画映射
    bottomTags: BottomTag[]; // 底部标签
    airborneAction: null; // 空中动作
    reward: null; // 奖励
    userTop: boolean; // 用户是否置顶
    highlight: boolean; // 是否高亮
    track: null; // 轨迹
}

// 用户信息
interface User {
    avatarDetail: null; // 头像详情
    commonIdentity: null; // 普通身份
    locationInfo: null; // 位置信息
    liveInfo: null; // 直播信息
    followed: boolean; // 是否已关注
    vipRights: VipRights | null; // 会员权益
    relationTag: null; // 关系标签
    anonym: number; // 匿名状态
    encryptUserId: string; // 加密用户 ID
    userId: number; // 用户 ID
    userType: number; // 用户类型
    nickname: string; // 昵称
    avatarUrl: string; // 头像 URL
    authStatus: number; // 认证状态
    expertTags: null; // 专家标签
    experts: null; // 专家信息
    vipType: number; // 会员类型
    remarkName: string | null; // 备注名称
    isHug: boolean; // 是否拥抱
    socialUserId: null; // 社交用户 ID
    target: null; // 目标
}

// 会员权益
interface VipRights {
    associator: Associator | null; // 联合会员
    musicPackage: MusicPackage | null; // 音乐套餐
    redplus: null; // 红加会员
    redVipAnnualCount: number; // 红会员年数
    redVipLevel: number; // 红会员等级
    relationType: number; // 关系类型
    memberLogo: null; // 会员标志
    extInfo: null; // 扩展信息
}

// 联合会员
interface Associator {
    vipCode: number; // 会员代码
    rights: boolean; // 权益
    iconUrl: string; // 图标 URL
}

// 音乐套餐
interface MusicPackage {
    vipCode: number; // 会员代码
    rights: boolean; // 权益
    iconUrl: string; // 图标 URL
}

// 被回复信息
interface BeReplied {
    user: User; // 用户信息
    beRepliedCommentId: number; // 被回复评论 ID
    commentId: number; // 评论 ID
    content: string; // 内容
    richContent: string | null; // 富文本内容
    status: number; // 状态
    expressionUrl: string | null; // 表情图片 URL
    contentResource: null; // 内容资源
    contentPicNosKey: string | null; // 内容图片 NOS Key
    contentPicUrl: string | null; // 内容图片 URL
    ipLocation: IPLocation; // IP 位置
    owner: boolean; // 是否是主人
}

// IP 位置
interface IPLocation {
    ip: string | null; // IP 地址
    location: string; // 位置
    userId: number; // 用户 ID
}

// 挂件数据
interface PendantData {
    id: number; // 挂件 ID
    imageUrl: string; // 图片 URL
}

// 显示楼中楼评论
interface ShowFloorComment {
    replyCount: number; // 回复数
    comments: null; // 评论列表
    showReplyCount: boolean; // 是否显示回复数
    topCommentIds: null; // 置顶评论 ID 列表
    target: null; // 目标
}

// 装饰信息
interface Decoration {
    repliedByAuthorCount: number; // 被作者回复数
}

// 标签
interface Tag {
    datas: null; // 数据
    extDatas: ExtData[]; // 扩展数据
    contentDatas: null; // 内容数据
    contentPicDatas: null; // 内容图片数据
    relatedCommentIds: null; // 相关评论 ID 列表
}

// 扩展数据
interface ExtData {
    text: string; // 文本
    iconUrl: string | null; // 图标 URL
    type: number; // 类型
    targetUrl: string; // 目标 URL
    recommendType: null; // 推荐类型
    commentType: null; // 评论类型
}

// 扩展信息
interface ExtInfo {
    forwardEvent: number; // 转发事件
    source: Source | null; // 来源
    statistics: Statistics | null; // 统计信息
}

// 来源
interface Source {
    keys: null; // 键
    id: number; // ID
    iconUrl: string | null; // 图标 URL
    text: string | null; // 文本
    type: number; // 类型
    orpheus: null; // Orpheus 信息
}

// 统计信息
interface Statistics {
    status_59: number; // 状态 59
    status_58: number; // 状态 58
    status_60: number | null; // 状态 60
}

// 评论视频信息
interface CommentVideoVO {
    showCreationEntrance: boolean; // 是否显示创作入口
    allowCreation: boolean; // 是否允许创作
    creationOrpheusUrl: string | null; // 创作 Orpheus URL
    playOrpheusUrl: string | null; // 播放 Orpheus URL
    videoCount: number; // 视频数量
    forbidCreationText: string; // 禁止创作文本
}

// 内容资源
interface ContentResource {
    userId: number | null; // 用户 ID
    userNickName: string | null; // 用户昵称
    resourceId: string; // 资源 ID
    resourceName: string | null; // 资源名称
    threadId: string | null; // 评论线程 ID
    artists: Artist[]; // 艺术家列表
    title: string; // 标题
    subTitle: string | null; // 子标题
    tag: string; // 标签
    coverUrl: string; // 封面 URL
    url: string | null; // URL
    shareUrl: string | null; // 分享 URL
    contentUrl: string | null; // 内容 URL
    duration: number | null; // 时长
}

// 艺术家
interface Artist {
    id: number; // 艺术家 ID
    name: string; // 艺术家名称
}

// 外部显示评论
interface OutShowComment {
    commentId: number; // 评论 ID
    userId: number; // 用户 ID
    content: string; // 内容
    liked: boolean; // 是否点赞
    likedCount: number; // 点赞数
    replyCount: number; // 回复数
    time: number; // 时间戳
    timeStr: string; // 时间字符串
    beReplied: BeReplied[] | null; // 被回复信息
}

// 点赞动画映射
interface LikeAnimationMap {
    [key: string]: boolean; // 点赞动画映射
}

// 底部标签
interface BottomTag {
    text: string; // 文本
    type: number; // 类型
}