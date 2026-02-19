import search from "@models/netease/search";

const song = await search(process.env.KEYWORDS) as any;

process.stdout.write(String(song.id) + "\n");
