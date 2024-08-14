import ffmpeg from 'fluent-ffmpeg';
import fs from 'node:fs'

fs.readdirSync('./assets', { withFileTypes: true, recursive: true }).forEach(file => {
  const { name } = file
  if (!file.isFile()) return
  ffmpeg.ffprobe(`./assets/${name}`, function (err, metadata) {
    if (err) {
      console.error('Not Media File:', err);
    } else {
      if (!fs.existsSync('./out')) {
        fs.mkdirSync('./out');
      }
      fs.writeFileSync(`./out/metadata-${name}.json`, JSON.stringify(metadata,
        null, 2));
    }
  });
});