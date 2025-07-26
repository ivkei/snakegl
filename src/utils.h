#pragma once

#include"logger.h"

#ifdef _SNAKEGL_DEBUG
#define ASSERT(x) if (!(x)) LOG_ASSERT("Assertion failed!")
#define _SNAKEGL_ENABLE_LOGGING
#else
#define ASSERT(x)
#endif

//Keys
#define SNAKEGL_KEY_W 0
#define SNAKEGL_KEY_A 1
#define SNAKEGL_KEY_S 2
#define SNAKEGL_KEY_D 3
#define SNAKEGL_KEY_SPC 4
#define SNAKEGL_KEY_ESC 5
