#include "video.h"
#include "macros.h"

#include <GL/glew.h>

static SDL_Window *window = NULL;

static SDL_GLContext *context = NULL;

static SDL_Renderer *renderer = NULL;


int video_initialise(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf_error("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

    if (window == NULL)
    {
        printf_error("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        printf_error("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return -1;
    }

    if (SDL_SetRenderDrawColor(renderer,
                VIDEO_BACKGROUND_R,
                VIDEO_BACKGROUND_G,
                VIDEO_BACKGROUND_B, 255) < 0)
    {
        printf_error("SDL_SetRenderDrawColor failed: %s\n", SDL_GetError());
        return -1;
    }

    context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        printf_error("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

void video_destroy(void)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_GL_DeleteContext(context);

    SDL_Quit();
}

int video_clear_screen(void)
{
    if (SDL_RenderClear(renderer) < 0) return -1;

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    /*SDL_GL_SwapWindow(indow);*/

    return 0;
}

void video_present(void)
{
    SDL_GL_SwapWindow(window);
    SDL_RenderPresent(renderer);
}


