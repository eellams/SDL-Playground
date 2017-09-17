#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <SDL2/SDL.h>

#define WINDOW_TITLE "Grid Path Finding"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define VIDEO_INIT_SUCCESS          0
#define VIDEO_INIT_ERROR_SDL_ERROR  1
#define VIDEO_INIT_ERROR_WINDOW     2
#define VIDEO_INIT_ERROR_RENDERER   3

int video_initialise(void);
int video_destroy(void);

#endif

