import getDetail from "@models/netease/detail";

const id:number = Number(process.env.SID);
const detail = await getDetail(id);

switch (process.env.TYPE) {
	case "fullname" :
//		process.stdout.write(detail.name);
		console.log(detail.name);
		break;
	case "artists" :
//		process.stdout.write(String(detail.artists.length) + "\n");
		console.log(String(detail.artists.length));
		let out = "";
		for(let i = 0; i < detail.artists.length; i++) {
			out += Buffer.from(detail.artists[i], "utf-8").length + " ";
		}
//		process.stdout.write(out + "\n");
		console.log(out);
		out = "";
		for(let i = 0; i < detail.artists.length; i++) {
			out += detail.artists[i];
		}
//		process.stdout.write(out + "\n");
		console.log(out);
		break;
	case "cover" :
//		process.stdout.write(detail.cover + "\n");
		console.log(detail.cover);
		break;
	case "album_id" :
//		process.stdout.write(detail.album.id + "\n");
		console.log(String(detail.album.id));
		break;
	case "album_name" :
//		process.stdout.write(detail.album.name + "\n");
		console.log(detail.album.name);
		break;
	default:
//		process.stdout.write("[Bad call]");
		console.log("[Bad call]");
}
