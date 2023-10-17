import os
import json
from PIL import Image

getIdByRGB = {
    0x000000: 0,
    0xFFFFFF: 1,
    0x313131: 2,
    0x969696: 3,
    0xFF1414: 4,
    0xF7CC18: 5,
    0x6EBED5: 6,
    0x1477AC: 7,
    0x57BB83: 8,
    0xEE378B: 9,
    0xF6940E: 10,
    0x2F1A0F: 11,
    0x60483C: 12,
    0xA47F2C: 13,
    0xFA8361: 14,
    0xFAD4B5: 15
}

getRBGAById = [
    0x000000FF, 0xFFFFFFFF, 0x313131FF, 0x969696FF, 0xFF1414FF, 0xF7CC18FF, 0x6EBED5FF, 0x1477ACFF,
    0x57BB83FF, 0xEE378BFF, 0xFA8361FF, 0x2F1A0FFF, 0x60483CFF, 0xA47F2CFF, 0xF6940EFF, 0xFAD4B5FF
]


def get_icon_from_file(path):
    if not os.path.exists(path):
        print(path, "Not Found")
        return [0] * 8

    image = Image.open(path)
    image = image.convert("RGBA")
    width, height = image.size

    array = [0] * 8

    for x in range(height):
        for y in range(width):
            red, green, blue, alpha = image.getpixel((y, x))

            # 获取RGBA值对应的id
            rgb_value = (red << 16) + (green << 8) + blue
            if rgb_value in getIdByRGB:
                id = getIdByRGB[rgb_value]
            else:
                print([red, green, blue, alpha], "Not Found")
                continue

            array[x] |= id << (y * 4)

    print(array)
    return array


arr = []
for i in range(91):
    icon = get_icon_from_file(f"../pixel/pixel/{i}.png")
    for j in range(8):
        arr.append(icon[j])

print(arr)
with open("pixel.txt", "w") as file:
    file.write(json.dumps(arr).replace("[", "{").replace("]", "}"))