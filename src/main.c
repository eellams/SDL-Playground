#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*#include "map.h"*/
#include "video.h"

/*#define SCREEN_WIDTH 20*32
#define SCREEN_HEIGHT 20*32*/


static int finished;

int event_loop(void);


/*int main(int argc, char* argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Event event;
    SDL_Rect rect;

    int i;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialise sdl2: %s\n", SDL_GetError());
        return 1;
    }

    srand(time(NULL));

    window = SDL_CreateWindow(
            "Hello SDL2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    //map_initialise(20,20);
    finished = 0;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    rect.x = 0;
    rect.y = 0;
    rect.w = 10;
    rect.h = 20;

    while (!finished)
    {
        event_loop();

        // Set background colour
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        //map_draw(renderer);


        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    //map_cleanup();

    return 0;
}*/

int init_video(void)
{
    int return_resp;

    return_resp = video_initialise();

    switch(return_resp)
    {
    case VIDEO_INIT_SUCCESS:
        goto rtn_success;
    case VIDEO_INIT_ERROR_SDL_ERROR:
        fprintf(stderr, "Error initialising SDL\n");
        break;
    case VIDEO_INIT_ERROR_WINDOW:
        fprintf(stderr, "Error opening window\n");
        break;
    case VIDEO_INIT_ERROR_RENDERER:
        fprintf(stderr, "Error creating renderer\n");
        break;
    default:
        fprintf(stderr, "Unknown error initialising video\n");
        break;
    }

    return 1;

rtn_success:
    return 0;
}

int main(int argc, char* argv[]) {
    if (init_video() != 0)
    {
        return 1;
    }

    SDL_Delay(1000);

    video_destroy();

    return 0;
}


// Process SDL events
int event_loop(void)
{
    SDL_Event event;


    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        finished = 1;
                        break;
                }
                break;
            case SDL_KEYUP:
                break;

            case SDL_WINDOWEVENT:
                switch(event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        finished = 1;
                        break;
                }
                break;
        }
    }

    return 0;
}

