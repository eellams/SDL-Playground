#ifndef VIDEO_H__
#define VIDEO_H__

#include <SDL2/SDL.h>

#define WINDOW_TITLE "Grid Path Finding"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define VIDEO_BACKGROUND_R 0
#define VIDEO_BACKGROUND_G 0
#define VIDEO_BACKGROUND_B 0 

int video_initialise(void);
void video_destroy(void);

int video_clear_screen(void);
void video_present(void);

#endif

