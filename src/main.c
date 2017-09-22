#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_opengl.h>

#include <GL/gl.h>

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

void draw_cube(void)
{
    glBegin(GL_QUADS);

    /* Cube Top */
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);


    /* Cube Bottom */
    glColor4f(1.0f, 0.5f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    /* Cube Front */
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    /* Cube Back */
    glColor4f(0.0f, 1.0f, 0.5f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    /* Cube Left Side */
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    /* Cube Right Side */
    glColor4f(0.15f, 0.25f, 0.75f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);


    glEnd();
    glLoadIdentity();
}

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


        /* TODO should probably implement a better frame limiter */
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

                    case SDLK_1:
                        video_set_ortho();
                        break;

                    case SDLK_2:
                        video_set_perspective();
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
    static GLfloat rotation = 0.0;

    /* Clear the screen */
    if (video_clear_screen() < 0) return -1;

    /* Set camera location etc. */
    if (video_set_camera() < 0) return -1;


    /* Show something interesting */
    glRotatef(rotation, 1.0f, 2.0f, 3.0f);
    rotation -= 0.5f;
    draw_cube();
       
    video_present();

    return 0;
}

