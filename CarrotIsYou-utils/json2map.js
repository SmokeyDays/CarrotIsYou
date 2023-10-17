const fs = require('fs');

// enum CIYType {
//   CARROT = 0, FLAG, WALL, ROCK, WATER, LAVA, ICE, HEART, WITCH, DOOR, KEY, BOX, STAR, SKULL, GHOST, BUG,
//   IS = 16, HAS, AND, EMPTY, ILLEGAL,
//   YOU = 24, WIN, PUSH, STOP, MELT, SINK, HOT, DEFEAT, OPEN, SHUT, WEAK, MOVE, FLOAT, TEXT, PULL, TELE,
//   CARROT_TEXT = 40, FLAG_TEXT, WALL_TEXT, ROCK_TEXT, WATER_TEXT, LAVA_TEXT, ICE_TEXT, HEART_TEXT, WITCH_TEXT, DOOR_TEXT, KEY_TEXT, BOX_TEXT, STAR_TEXT, SKULL_TEXT, GHOST_TEXT, BUG_TEXT
// }

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

function loadBoardFromFile(path) {
  let ret = [];
  fs.readFile(path, 'utf-8', (err, data) => {
    if (err) {
      console.error('Error reading JSON file:', err);
      return;
    }
    let board = JSON.parse(data);
    ret.push(board.width);
    ret.push(board.height);
    for (let i = 0; i < board.objects.length; i++) {
      let obj = board.objects[i];
      let type = typeStr2typeId[obj.type];
      let x = obj.x;
      let y = obj.y;
      let d = obj.d;
      let val = (x & 0xF) | ((y & 0xF) << 4) | ((d & 0x3) << 8) | ((type & 0x3F) << 10);
      ret.push(val);
      console.log(`Analyzed object ${i}: type=${type}, x=${x}, y=${y}, d=${d}, val=0x${val.toString(16)}`);
    }
    ret.unshift(ret.length + 1);
    console.log(ret);
  });
}

function writeBoardToFile(path, board) {
  fs.writeFile(path, JSON.stringify(board), (err) => {
    if (err) {
      console.error('Error writing JSON file:', err);
      return;
    }
    console.log('JSON file saved.');
  });
}

function createBoard(width, height) {
  let board = {
    width: width,
    height: height,
    objects: []
  };
  return board;
}

function insertObject(board, type, x, y, d) {
  let obj = {
    type: type,
    x: x,
    y: y,
    d: d
  };
  board.objects.push(obj);
  return board;
}

board = createBoard(16, 8);
board = insertObject(board, "CARROT_TEXT", 0, 0, 0);
board = insertObject(board, "IS", 0, 1, 0);
board = insertObject(board, "YOU", 0, 3, 0);
board = insertObject(board, "FLAG_TEXT", 0, 4, 0);
board = insertObject(board, "IS", 0, 5, 0);
board = insertObject(board, "WIN", 0, 6, 0);
board = insertObject(board, "WALL_TEXT", 0, 7, 0);
board = insertObject(board, "IS", 0, 8, 0);
board = insertObject(board, "STOP", 0, 9, 0);
board = insertObject(board, "ROCK_TEXT", 0, 10, 0);
board = insertObject(board, "IS", 0, 11, 0);
board = insertObject(board, "PUSH", 0, 12, 0);

board = insertObject(board, "CARROT", 5, 3, 0);
board = insertObject(board, "FLAG", 5, 13, 0);

for(let i = 0; i < 16; i++) {
  board = insertObject(board, "WALL", 1, i, 0);
  board = insertObject(board, "WALL", 7, i, 0);
}
for(let i = 2; i < 7; i++) {
  board = insertObject(board, "ROCK", i, 8, 0);
}

writeBoardToFile('./src/map/1.json', board);

loadBoardFromFile('./src/map/1.json');