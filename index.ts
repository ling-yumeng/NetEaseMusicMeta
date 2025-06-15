import getLyric from "@models/netease/lyric";
import getDetail from "@models/netease/detail";
import writeMetadataWithFFmpeg from "@utils/ffmpeg/writeMetadata";
import readMetadata from "@utils/ffmpeg/readMetadata";
let id = 2034361036

getDetail(id).then(async (detail) => {
  if (!detail) return;
  writeMetadataWithFFmpeg(
    "/home/ml/下载/64Gram Desktop/免我蹉跎苦 (Single Version)-阿萨Aza.ogg.mp3",
    detail,
    await getLyric(id)
  );
});

//readMetadata("/home/ml/下载/64Gram Desktop/免我蹉跎苦 (Single Version)-阿萨Aza.ogg.mp3").then(console.log)