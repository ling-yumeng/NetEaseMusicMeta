import getLyric from "@models/netease/lyric";
import getDetail from "@models/netease/detail";

let id = 2034361036

getLyric(id).then(console.log);
getDetail(id).then(console.log);