import ffmpeg from 'fluent-ffmpeg';

export default function readMetadata(filePath: string): Promise<Record<string, any>> {
  return new Promise((resolve, reject) => {
    ffmpeg.ffprobe(filePath, (err, metadata) => {
      if (err) return reject(err);

      const formatTags = metadata?.format?.tags ?? {};
      resolve(formatTags);
    });
  });
}
