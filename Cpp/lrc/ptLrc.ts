import getLyric from "@models/netease/lyric";

async function main() {
	const lrc = await getLyric(process.env.SID);
	console.log(lrc);
}

main()
