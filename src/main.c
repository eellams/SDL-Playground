#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*#include "map.h"*/
#include "video.h"

#include "macros.h"

static int finished;

int event_loop(void);

int update(void);
int render(void);

int main(int argc, char* argv[]) {
    printf_info("%s", "Startup\n");
    if (video_initialise() < 0)
    {
        puts("Error initialising videos, exiting.\n");
        return 1;
    }

    while (!finished)
    {
        /* If an error while updating */
        if (update() < 0) goto main_cleanup;

        /* If an error occurred while rendering */
        if (render() < 0) goto main_cleanup;

        SDL_Delay(10);
    }

main_cleanup:

    video_destroy();

    printf_info("%s", "Exiting\n");
    return 0;
}


/* Process SDL events */
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

/* Update everything */
int update(void)
{
    if(event_loop() < 0)
    {
        return -1;
    }
    return 0;
}

/* Render everything */
int render(void)
{
    /* Clear the screen */
    if (video_clear_screen() < 0) return -1;

    /* Present the renderer(s) when ready */
    video_present();

    return 0;
}

