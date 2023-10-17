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


def get_icons_from_file(path):

    image = Image.open(path)
    image = image.convert("RGBA")
    width, height = image.size
    print(range(width), range(height))

    total = []

    array = [0] * 8

    for big_id in range(0, 106):
        big_x = big_id % 64
        big_y = big_id // 64
        print(big_x, big_y)
        for x in range(0, 8):
            for y in range(0, 8):
                # print(big_y * 8 + y, big_x * 8 + x)
                red, green, blue, alpha = image.getpixel((big_y * 8 + y, big_x * 8 + x))

                # 获取RGBA值对应的id
                rgb_value = (red << 16) + (green << 8) + blue
                print([red, green, blue, alpha], rgb_value)
                if rgb_value in getIdByRGB:
                    id = getIdByRGB[rgb_value]
                    print(id)
                else:
                    print([red, green, blue, alpha], "Not Found")
                    continue

                array[x] |= id << (y * 4)
        for j in range(8):
            total.append(array[j])
        array = [0] * 8

    print(total)
    return total

arr = get_icons_from_file("../pixel/pixel/icons.png")

print(arr)
with open("pixel.txt", "w") as file:
    file.write(json.dumps(arr).replace("[", "{").replace("]", "}"))