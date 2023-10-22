#ifndef TETRIS_INPUT
#define TETRIS_INPUT

#include "libdevice.h"

// A couple structs that contain key/mouse button status
// There is a "current" state and an "old" state (previous frame)

int getKey();

// Wait any key in kaymap down.
// During waiting, any key code will be ignored.
void wait_any_key_down(struct KeyMap* key);
#endif
