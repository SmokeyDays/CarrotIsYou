#include "CarrotOS.h"
#include "./lib/MiniMalloc.h"
#include<cstdio>

const unsigned int pixel[] = 
{2236928, 48373760, 788406784, 2399135778, 3793104608, 576859886, 4062376448, 572662304, 331776, 1380608, 22368528, 1431655697, 2857719125, 178607440, 11162880, 675840, 0, 557056, 9209856, 13421696, 214748352, 3418148044, 3149647035, 3149642683, 3355392, 53686832, 36844339, 857944867, 589509155, 573776674, 572662306, 35791392, 7827456, 2004317952, 1897297776, 1719101303, 1717985639, 1986422391, 1980852080, 124221184, 262144, 262144, 263168, 67388416, 72000516, 1152013380, 1252371008, 77964288, 1717986918, 1610612742, 1616905734, 1611006054, 1711300614, 1616905734, 1610612742, 1717986918, 0, 160434576, 2576980249, 2576980249, 2576980249, 161059216, 10066176, 626688, 1118464, 26284032, 435753216, 1509922065, 2433227152, 293673369, 4044484864, 286331152, 196852656, 197971120, 197971120, 197971376, 197971376, 197971120, 197971120, 196852656, 0, 56784, 21853, 3722268677, 1431654405, 1347444181, 21840, 0, 1020054723, 3453869532, 3453869532, 3453869532, 1019219139, 3148876731, 3149015995, 3149642683, 5591040, 89128960, 1426063360, 2768240640, 2768240640, 2773483525, 2857697360, 178607360, 1118480, 17895697, 286331153, 287445282, 285348098, 554766353, 34672914, 1184272, 0, 2306816, 36909872, 554897715, 538116403, 573780787, 573780787, 573584131, 7829248, 126316544, 2029549312, 2566883703, 2266331264, 2002221192, 4151834368, 2004318064, 257, 256, 1118481, 1048832, 1052688, 1048592, 1114113, 0, 256, 17895697, 1114368, 1048592, 17895697, 65552, 69648, 0, 16, 17895696, 16, 1118480, 1048576, 1052945, 1114112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 67108868, 4194368, 263168, 16384, 263168, 4194368, 67108868, 0, 285212689, 268435457, 0, 0, 0, 0, 268435457, 285212689, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 250486302, 17899038, 31580433, 249687582, 236002846, 31580446, 249634334, 0, 85283089, 85266769, 17895697, 85283153, 17912081, 85283153, 17912145, 0, 51581715, 17896209, 51581203, 17896211, 51581713, 51581715, 17896209, 0, 214703308, 214703308, 202447900, 214703132, 214703132, 214703132, 17895697, 0, 102109457, 17916182, 23159062, 17895697, 102110817, 18223377, 17897057, 0, 17895793, 24605047, 118560625, 118953847, 118953841, 118953841, 18313585, 0, 71570452, 68227345, 68424724, 68424721, 18104596, 71582788, 21053761, 0, 68227396, 71386129, 17895700, 68228116, 68424724, 21238804, 17896513, 0, 17895697, 220058077, 220058077, 17895697, 220058077, 220058077, 220060945, 0, 34742802, 35791394, 17895697, 35787298, 17895697, 35725602, 17965585, 0, 107372902, 17916262, 23488017, 23467542, 23486822, 23467542, 102109457, 0, 142704913, 17897608, 25264401, 25266200, 25264513, 25264401, 18354568, 0, 17917537, 102109542, 107374177, 101783142, 102131297, 17895777, 107046497, 0, 35787298, 17895697, 18944289, 35725858, 17895697, 35787298, 35787042, 0, 231857437, 17895697, 220011805, 220011805, 220011793, 231808285, 17895697, 0, 17895825, 26841497, 26284433, 26841497, 26284433, 26284433, 18452881, 0, 57344, 250535936, 57344, 250539758, 57344, 14737408, 234938368, 0, 20480, 89478485, 84235525, 20480, 349440, 5263360, 89478485, 0, 49152, 49152, 201375756, 201375756, 201375756, 201375756, 214748364, 0, 53687091, 12288, 768, 53687088, 50332419, 50332416, 53687040, 0, 28672, 117469184, 7370615, 489216, 7368816, 117469191, 30464, 0, 16384, 16384, 4210752, 278592, 16384, 263168, 71303236, 0, 393222, 101056512, 6710784, 417792, 6686214, 101056518, 417798, 0, 2304, 36864, 2304, 9439632, 150997392, 9439497, 10066176, 0, 10027017, 9474048, 589833, 160471296, 10063881, 9474057, 10063881, 0, 214748172, 201326592, 201326604, 201326604, 201326604, 201326604, 213909516, 0, 89456720, 84215045, 89456640, 84213845, 89458000, 84213845, 89150800, 0, 232587472, 855517, 232587472, 218959325, 232587485, 852176, 232587472, 0, 178956800, 167774720, 178956800, 167774720, 178956800, 167774720, 178258080, 0, 1052944, 17895440, 1052945, 1052673, 17891600, 16843024, 17891600, 0, 53687091, 50331648, 53687091, 12288, 3158064, 197376, 53477427, 0, 32768, 32768, 557056, 8421376, 134250496, 32768, 32768, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 235802350, 917728, 250539758, 917728, 235802350, 14680288, 235856110, 0, 4096, 1118481, 1048576, 65536, 4352, 16777232, 1118465, 0, 328960, 89456720, 348245, 89456720, 327760, 89456720, 327760, 0, 0, 0, 17891328, 268439553, 257, 17, 4369, 0, 4369, 16781568, 268439568, 268439553, 268435457, 268435457, 16777232, 1118464, 49152, 49152, 13418496, 49152, 49152, 49152, 214748364, 0, 214748364, 49152, 49152, 12632064, 201375744, 49152, 49152, 0, 3328, 232644061, 3328, 14540032, 852176, 851981, 232644048, 0, 53248, 232644061, 3328, 14540240, 13634829, 13634816, 14540032, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6291456, 107374182, 0, 0, 0, 0, 0, 6710880, 0, 0, 0, 107374182, 0, 0, 107374182, 0, 0, 6710880, 0, 0, 107374182, 0, 107374182, 101058054, 101058054, 107349510, 100663398, 100663302, 107374182, 0, 6710784, 24576, 24576, 6710880, 6292992, 6292992, 107374182, 0, 24576, 107374182, 0, 394752, 394752, 6291552, 100663302, 0, 1536, 1536, 107349504, 26214, 1536, 100664832, 107372544, 0, 394752, 394752, 394752, 394752, 6291552, 6291552, 100663302, 0, 1536, 419430, 394752, 394752, 394752, 101056608, 107347974, 0, 24576, 24576, 107374182, 24576, 24576, 24576, 24576, 0, 0, 0, 65536, 4096, 256, 0, 0, 0, 0, 209664, 196608, 12288, 12288, 768, 209664, 0, 0, 13056, 197376, 197376, 13056, 768, 768, 0, 0, 12288, 197376, 197376, 197376, 12288, 196608, 0, 0, 13056, 197376, 197376, 13056, 197376, 197376, 0, 458864, 125269879, 117901168, 125269872, 7368823, 7798896, 117471095, 0, 8390656, 134744064, 143165576, 32896, 143132800, 134776832, 143130760, 0, 4472832, 71582720, 71582720, 3427025920, 71582720, 67125312, 4195332, 0, 196804608, 3149639680, 3220945664, 3489659648, 268419072, 15728640, 560013312, 560015104, 526336, 559104, 559104, 559232, 2148048896, 2282269184, 8945664, 131584, 0, 17764368, 987136, 17145872, 368640, 17145872, 368640, 0, 4473860, 4210692, 4210688, 71581696, 67108868, 67388420, 71303172, 0, 789504, 789504, 202116108, 13372608, 789504, 789504, 214748364, 0, 49152, 214748364, 12583104, 838656, 213912780, 12585984, 12583104, 0, 125269767, 117440512, 117929735, 117440519, 117929735, 117440519, 117929735, 0, 125241095, 117440512, 125269767, 117901056, 125269767, 117442311, 124782343, 0, 107349504, 101082726, 6686208, 101082726, 101058048, 6710886, 393312, 0, 12288, 53687091, 209664, 53686323, 196608, 53687091, 12288, 0, 3354627, 196608, 53687043, 3145731, 53687043, 3158019, 3342387, 0, 143132808, 134744072, 134742152, 143132680, 134744200, 134742024, 143130632, 0, 168430080, 178956970, 657920, 178299050, 657920, 178956970, 10485920, 0, 20480, 89478485, 84235605, 80, 5592400, 329040, 89150725, 0}
;
enum CIYIcon {
  ICON_ME = 64, ICON_MY, ICON_WORK, ICON_UNDO, ICON_RESTART, ICON_UP, ICON_DOWN, ICON_LEFT, ICON_RIGHT, ICON_73, ICON_1, ICON_2, ICON_3, ICON_4, ICON_5, ICON_6, ICON_7, ICON_8, ICON_9, ICON_10, ICON_SLASH, ICON_Z, ICON_P, ICON_Q, ICON_R, ICON_PRESS, ICON_START, ICON_OCTUPOS, ICON_BANGBANG, ICON_YANGYANG, ICON_GC, ICON_FENG, ICON_YE, ICON_QI, ICON_YAN, ICON_RUN, ICON_BANG, ICON_LI, ICON_SHI, ICON_YANG, ICON_GONG, ICON_CHEN
};
void CarrotOS::renderIcon(int x, int y, int type, int times) {
  for(int i = 0; i < 8; ++i) {
    unsigned int val = pixel[type * 8 + i];
    unsigned int real[16];
    for(int j = 0; j < times; ++j) {
      real[j] = 0;
    }
    for(int j = 0; j < 8; ++j) {
      for(int k = 0; k < times; ++k) {
        real[(j * times + k) / 8] |= ((val >> (j * 4)) & 0xF) << ((j * times + k) % 8 * 4);
      }
    }
    for(int j = 0; j < times; ++j) {
      for(int k = 0; k < times; ++k) {
        #ifdef CARROT_ON_SDL
          setDisplayMemory(x * 8 + i * times + j, y + k, real[k]);
        #endif
      }
    }
  }
}

void CarrotOS::renderTest() {
#ifdef CARROT_ON_SDL
  clearDisplayMemory();
#endif
  for(int i = 0; i < 16; ++i) {
    for(int j = 0; j < 16; ++j) {
      renderIcon(i, j, i * 16 + j, 1);
    }
  }
#ifdef CARROT_ON_SDL
  sdlUpdate();
#endif
}

void CarrotOS::renderInit() {
#ifdef CARROT_ON_SDL
  clearDisplayMemory();
#endif
  renderIcon(6, 4, CARROT_TEXT, 2);
  renderIcon(6, 6, WITCH_TEXT, 2);
  renderIcon(6, 8, IS, 2);
  renderIcon(6, 10, YOU, 2);

#ifdef CARROT_ON_SDL
  sdlUpdate();
#endif
}

void CarrotOS::renderGameStart() {
#ifdef CARROT_ON_SDL
  clearDisplayMemory();
#endif
  
#ifdef CARROT_ON_SDL
  sdlUpdate();
#endif
}

void CarrotOS::renderGameRunning() {
#ifdef CARROT_ON_SDL
  clearDisplayMemory();
#endif
  const BufVector<CIYObject, MAX_OBJ_NUM> &objs = core.getBoard().getObjects();
  const BufVector<CIYObject, MAX_ILLEGAL_NUM> &illegalObjects = core.getBoard().getIllegalObjects();
  BufVector<CIYObject, MAX_OBJ_NUM> winObjs = core.getBoard().getWinObjs();

  for(int i = 0; i < objs.size(); ++i) {
    renderIcon(objs[i].x(), objs[i].y(), objs[i].type(), 1);
  }
  for(int i = 0; i < illegalObjects.size(); ++i) {
    renderIcon(illegalObjects[i].x(), illegalObjects[i].y(), illegalObjects[i].type(), 1);
  }
  for(int i = 0; i < winObjs.size(); ++i) {
    renderIcon(winObjs[i].x(), winObjs[i].y(), TO_WIN, 1);
  }

  if(core.isWinning()) {
    renderIcon(6, 4, WIN, 2);
    renderIcon(6, 8, IS, 2);
    renderIcon(6, 12, YOU, 2);
  }
#ifdef CARROT_ON_SDL
  sdlUpdate();
#endif
}

void CarrotOS::run() {
  // renderTest();
  renderInit();
  while(true) {
    switch(state) {
      case OS_INIT:
        if (!keyEmpty()) {
          int keyInput = keyPop();
          switch (keyInput) {
            case KEY_ENTER:
              renderGameStart();
              state = OS_GAME_START;
              break;
          }
        }
        break;
      case OS_GAME_START:
        if (!keyEmpty()) {
          int keyInput = keyPop();
          switch (keyInput) {
            case KEY_ENTER:
              core.init(level);
              renderGameRunning();
              state = OS_GAME_RUNNING;
              break;
          }
        }
        break;
      case OS_GAME_RUNNING:
        if (!keyEmpty()) {
          int keyInput = keyPop();
          switch (keyInput) {
            case KEY_UP:
              core.move(0);
              break;
            case KEY_RIGHT:
              core.move(1);
              break;
            case KEY_DOWN:
              core.move(2);
              break;
            case KEY_LEFT:
              core.move(3);
              break;
            case KEY_KEEP:
              core.move(-1);
              break;
            case KEY_UNDO:
              core.undo();
              break;
            case KEY_RESTART:
              core.init(level);
              break;
            case KEY_BACK:
              if (level > 1) {
                level--;
              }
              core.init(level);
              break;
            case KEY_NEXT: 
              if (level < LEVEL_MAX) {
                level++;
              }
              core.init(level);
              break;
          }
          renderGameRunning();
        }
        break;
    }
  }
}