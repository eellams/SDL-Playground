#include "video.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;


int video_initialise(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return VIDEO_INIT_ERROR_SDL_ERROR;
    }

    window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

    if (window == NULL)
    {
        return VIDEO_INIT_ERROR_WINDOW;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        return VIDEO_INIT_ERROR_RENDERER;
    }

    return VIDEO_INIT_SUCCESS;
}

int video_destroy(void)
{
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


