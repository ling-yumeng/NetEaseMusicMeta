import getDetail from "@models/netease/detail";

const id:number = Number(process.env.SID);
const detail = await getDetail(id);

switch (process.env.TYPE) {
	case "fullname" :
		console.log(detail.name);
		break;
	case "artists" :
		console.log(detail.artists.length);
		let out = "";
		for(let i = 0; i < detail.artists.length; i++) {
			out += Buffer.from(detail.artists[i], "utf-8").length + " ";
		}
		console.log(out);
		out = "";
		for(let i = 0; i < detail.artists.length; i++) {
			out += detail.artists[i];
		}
		console.log(out);
		break;
	case "cover" :
		console.log(detail.cover);
		break;
	case "album_id" :
		console.log(detail.album.id);
		break;
	case "album_name" :
		console.log(detail.album.name);
		break;
	default:
		console.log("[Bad call]");
}
