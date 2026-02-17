import getDetail from "@models/netease/detail";

const id:number = Number(process.env.SID);
const detail = await getDetail(id);

switch (process.env.TYPE) {
	case "fullname" :
		process.stdout.write(detail.name + "\n");
		break;
	case "artists" :
		process.stdout.write(String(detail.artists.length) + "\n");
		let out = "";
		for(let i = 0; i < detail.artists.length; i++) {
			out += Buffer.from(detail.artists[i], "utf-8").length + " ";
		}
		process.stdout.write(out + "\n");
		out = "";
		for(let i = 0; i < detail.artists.length; i++) {
			out += detail.artists[i];
		}
		process.stdout.write(out + "\n");
		break;
	case "cover" :
		process.stdout.write(detail.cover + "\n");
		break;
	case "album_id" :
		process.stdout.write(detail.album.id + "\n");
		break;
	case "album_name" :
		process.stdout.write(detail.album.name + "\n");
		break;
	default:
		process.stdout.write("[Bad call]");
}
