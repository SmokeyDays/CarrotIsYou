const fs = require('fs');
const PNG = require('pngjs').PNG;

// 读取PNG文件
const file = fs.createReadStream('a.png');
const png = new PNG();

file.pipe(png);

png.on('parsed', function() {
  const width = png.width;
  const height = png.height;

  // 存储每个像素的RGBA值的数组
  const rgbaArray = [];

  // 遍历每个像素
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      const idx = (width * y + x) << 2;

      const red = png.data[idx];
      const green = png.data[idx + 1];
      const blue = png.data[idx + 2];
      const alpha = png.data[idx + 3];

      // 存储RGBA值到数组
      rgbaArray.push(red, green, blue, alpha);
    }
  }

  // 输出RGBA值数组
  console.log(rgbaArray);
});