import search from "@models/netease/search";

const song = await search(process.env.KEYWORDS) as any;

console.log(song.id);
