import json
import csv

typeStr2typeId = {
  "CARROT": 0, "FLAG": 1, "WALL": 2, "ROCK": 3, "WATER": 4, "LAVA": 5, "ICE": 6, "HEART": 7, "WITCH": 8, "DOOR": 9, "KEY": 10, "BOX": 11, "STAR": 12, "SKULL": 13, "GHOST": 14,
   "BUG": 15,
  "IS": 16, "HAS": 17, "AND": 18, "EMPTY": 19, "ILLEGAL": 20,
  "YOU": 24, "WIN": 25, "PUSH": 26, "STOP": 27, "MELT": 28, "SINK": 29, "HOT": 30, "DEFEAT": 31, "OPEN": 32, "SHUT": 33, "WEAK": 34, "MOVE": 35, "FLOAT": 36, "TEXT": 37, "PULL": 38, "TELE": 39,
  "CARROT_TEXT": 40, "FLAG_TEXT": 41, "WALL_TEXT": 42, "ROCK_TEXT": 43, "WATER_TEXT": 44, "LAVA_TEXT": 45, "ICE_TEXT": 46, "HEART_TEXT": 47, "WITCH_TEXT": 48, "DOOR_TEXT": 49,
   "KEY_TEXT": 50, "BOX_TEXT": 51, "STAR_TEXT": 52, "SKULL_TEXT": 53, "GHOST_TEXT": 54, "BUG_TEXT": 55

}
typeId2typeStr = {
  0: "CARROT", 1: "FLAG", 2: "WALL", 3: "ROCK", 4: "WATER", 5: "LAVA", 6: "ICE", 7: "HEART", 8: "WITCH", 9: "DOOR", 10: "KEY", 11: "BOX", 12: "STAR", 13: "SKULL", 14: "GHOST",
    15: "BUG",
  16: "IS", 17: "HAS", 18: "AND", 19: "EMPTY", 20: "ILLEGAL",
  24: "YOU", 25: "WIN", 26: "PUSH", 27: "STOP", 28: "MELT", 29: "SINK", 30: "HOT", 31: "DEFEAT", 32: "OPEN", 33: "SHUT", 34: "WEAK", 35: "MOVE", 36: "FLOAT", 37: "TEXT", 38: "PULL", 39: "TELE",
  40: "CARROT_TEXT", 41: "FLAG_TEXT", 42: "WALL_TEXT", 43: "ROCK_TEXT", 44: "WATER_TEXT", 45: "LAVA_TEXT", 46: "ICE_TEXT", 47: "HEART_TEXT", 48: "WITCH_TEXT", 49: "DOOR_TEXT",
    50: "KEY_TEXT", 51: "BOX_TEXT", 52: "STAR_TEXT", 53: "SKULL_TEXT", 54: "GHOST_TEXT", 55: "BUG_TEXT"
}

def pressBoard(data):
  ret = []
  ret.append(data['width'])
  ret.append(data['height'])
  for obj in data['objects']:
      type = typeStr2typeId[obj['type']]
      x = obj['x']
      y = obj['y']
      d = obj['d']
      val = (x & 0xF) | ((y & 0xF) << 4) | ((d & 0x3) << 8) | ((type & 0x3F) << 10)
      ret.append(val)
      # print(f"Analyzed object {len(ret) - 3}: type={type}, x={x}, y={y}, d={d}, val=0x{hex(val)}")
  ret.insert(0, len(ret) + 1)
  # print(ret)
  return ret

def writeBoardToFile(path, board):
    with open(path, 'w') as file:
        json.dump(board, file)
    print('JSON file saved.')

def createBoard(width, height):
    board = {
        'width': width,
        'height': height,
        'objects': []
    }
    return board

def insertObject(board, type, x, y, d):
    obj = {
        'type': type,
        'x': x,
        'y': y,
        'd': d
    }
    board['objects'].append(obj)
    return board

def readCSVFile(file_path):
    data = []
    with open(file_path, 'r',encoding = 'utf-8-sig') as file:
        reader = csv.reader(file)
        for row in reader:
            data.append(row)
    return data

def getBoardFromCSV(file_path):
    data = readCSVFile(file_path)
    width = min(len(data[0]), 16)
    height = min(len(data), 16)
    board = createBoard(width, height)
    for y in range(width):
        for x in range(height):
            if data[x][y] != '':
                print(data[x][y])
                board = insertObject(board, typeId2typeStr.get(int(data[x][y])), x, y, 0)
    return board

def level_1():
  board = createBoard(8, 16)
  board = insertObject(board, "CARROT_TEXT", 0, 0, 0)
  board = insertObject(board, "IS", 0, 1, 0)
  board = insertObject(board, "YOU", 0, 2, 0)
  board = insertObject(board, "FLAG_TEXT", 0, 4, 0)
  board = insertObject(board, "IS", 0, 5, 0)
  board = insertObject(board, "WIN", 0, 6, 0)
  board = insertObject(board, "WALL_TEXT", 0, 8, 0)
  board = insertObject(board, "IS", 0, 9, 0)
  board = insertObject(board, "STOP", 0, 10, 0)
  board = insertObject(board, "ROCK_TEXT", 0, 12, 0)
  board = insertObject(board, "IS", 0, 13, 0)
  board = insertObject(board, "PUSH", 0, 14, 0)

  board = insertObject(board, "CARROT", 5, 3, 0)
  board = insertObject(board, "FLAG", 5, 13, 0)

  for i in range(0, 16):
    board = insertObject(board, "WALL", 1, i, 0)
    board = insertObject(board, "WALL", 7, i, 0)
  for i in range(2, 7):
    board = insertObject(board, "ROCK", i, 8, 0)
  return board

def level_2():
  board = createBoard(16, 16)
  board = insertObject(board, "CARROT", 12, 12, 0)
  board = insertObject(board, "CARROT_TEXT", 1, 1, 0)
  board = insertObject(board, "IS", 2, 1, 0)
  board = insertObject(board, "YOU", 3, 1, 0)
  board = insertObject(board, "FLAG", 7, 6, 0)
  board = insertObject(board, "FLAG_TEXT", 7, 2, 0)
  board = insertObject(board, "IS", 2, 6, 0)
  board = insertObject(board, "WIN", 4, 11, 0)
  board = insertObject(board, "WALL_TEXT", 11, 8, 0)
  board = insertObject(board, "IS", 12, 8, 0)
  board = insertObject(board, "STOP", 13, 8, 0)
  for i in range(4, 16):
    board = insertObject(board, "WALL", 0, i, 0)
  for i in range(0, 5):
    board = insertObject(board, "WALL", i, 4, 0)
  for i in range(0, 5):
    board = insertObject(board, "WALL", 5, i, 0)
  for i in range(5, 9):
    board = insertObject(board, "WALL", i, 0, 0)
  for i in range(0, 15):
    board = insertObject(board, "WALL", 9, i, 0)
  for i in range(0, 16):
    board = insertObject(board, "WALL", i, 15, 0)
  for i in range(10, 16):
    board = insertObject(board, "WALL", i, 4, 0)
  for i in range(4, 16):
    board = insertObject(board, "WALL", 15, i, 0)
  return board

def level_3():
  board = getBoardFromCSV("../pixel/levels/rockiswin.csv")
  return board

def level_4():
  board = getBoardFromCSV("../pixel/levels/skullisdefeat.csv")
  return board

def level_5():
  board = getBoardFromCSV("../pixel/levels/wallisyou.csv")
  return board

def level_6():
  board = getBoardFromCSV("../pixel/levels/wallisnotstop.csv")
  return board

def level_7():
  board = getBoardFromCSV("../pixel/levels/rotate.csv")
  return board

def level_8():
  board = getBoardFromCSV("../pixel/levels/wallisnotstop.csv")
  return board

total = [0] * 16
total[0] = 8 # Total Level Num
for i in range(1, total[0] + 1):
  arr = pressBoard(eval(f'level_{i}()').copy())
  total[i] = len(total)
  for j in arr:
    total.append(j)

print(total)
with open("level.txt", "w") as file:
    file.write(json.dumps(total).replace("[", "{").replace("]", "}"))


