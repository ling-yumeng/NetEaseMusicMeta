import getLyric from "@models/netease/lyric";
import getDetail from "@models/netease/detail";
import search from "@models/netease/search";
import writeMetadataWithFFmpeg from "@utils/ffmpeg/writeMetadata";
import readMetadata from "@utils/ffmpeg/readMetadata";
import getComments from "@models/netease/comments";

// getDetail(id).then(async (detail) => {
//   if (!detail) return;
//   writeMetadataWithFFmpeg(
//     "/home/ml/下载/64Gram Desktop/免我蹉跎苦 (Single Version)-阿萨Aza.ogg.mp3",
//     detail,
//     await getLyric(id)
//   );
// });

//readMetadata("/home/ml/下载/64Gram Desktop/免我蹉跎苦 (Single Version)-阿萨Aza.ogg.mp3").then(console.log)

const id = await search("创作者之死") as any

console.log(await getDetail(id.id))
// console.log(id)
// console.log(JSON.stringify(await getComments(id.id)))

// import getSong from "@models/netease/player";

// console.log(await getSong(id.id))