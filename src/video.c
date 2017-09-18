#include "video.h"
#include "macros.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;


int video_initialise(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {

        printf("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

    if (window == NULL)
    {
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        return -1;
    }

    if (SDL_SetRenderDrawColor(renderer,
                VIDEO_BACKGROUND_R,
                VIDEO_BACKGROUND_G,
                VIDEO_BACKGROUND_B, 255) < 0)
    {
        return -1;
    }

    return 0;
}

void video_destroy(void)
{
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int video_clear_screen(void)
{
    
    return 0;
}


