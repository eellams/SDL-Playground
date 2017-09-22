#include "video.h"
#include "macros.h"

#include <GL/glew.h>

#define VECTOR_X 0
#define VECTOR_Y 1
#define VECTOR_Z 2

static SDL_Window *window = NULL;
static SDL_GLContext *context = NULL;
static SDL_Renderer *renderer = NULL;

/* Will perform cross product multiplication for two vector3s,
 *  storing result in res */
static void vector_crossprod(const float* a, const float *b, float *res)
{
    res[VECTOR_X] = a[VECTOR_Y]*b[VECTOR_Z] - a[VECTOR_Z]*b[VECTOR_Y];
    res[VECTOR_Y] = a[VECTOR_Z]*b[VECTOR_X] - a[VECTOR_X]*b[VECTOR_Z];
    res[VECTOR_Z] = a[VECTOR_X]*b[VECTOR_Y] - a[VECTOR_Y]*b[VECTOR_X];
}

/* Own implementation of gluLookAt */
static int custom_gluLookAt(const float eyeX, const float eyeY, const float eyeZ,
        const float targetX, const float targetY, const float targetZ,
        const float upX, const float upY, const float upZ)
{
    float fMag, upMag;
    float f[3];
    float up[3];

    float s[3];
    float u[3];
    float m[16];

    f[VECTOR_X] = targetX - eyeX;
    f[VECTOR_Y] = targetY - eyeY;
    f[VECTOR_Z] = targetZ - eyeZ;

    /* Normalise vcectors */
    fMag = sqrt(f[0]*f[0] + f[1]*f[1] + f[2]*f[2]);
    upMag = sqrt(upX*upX + upY*upY + upZ*upZ);

    /* Error, we need a magnitude (otherwise would divide by 0 */
    if (fMag == 0.0 || upMag == 0.0) return -1;

    /* Normalise */
    f[VECTOR_X] = f[VECTOR_X]/fMag;
    f[VECTOR_Y] = f[VECTOR_Y]/fMag;
    f[VECTOR_Z] = f[VECTOR_Z]/fMag;
    up[VECTOR_X] = upX/upMag;
    up[VECTOR_Y] = upY/upMag;
    up[VECTOR_Z] = upZ/upMag;

    /* Calculate required cross products */
    vector_crossprod(f, up, s);
    vector_crossprod(s, f, u);

    /* A bit hacky, but set the projection matrix */
    m[0] = s[0];  m[1] = u[0];  m[2] =-f[0];  m[3] = 0.0;
    m[4] = s[1];  m[5] = u[1];  m[6] =-f[1];  m[7] = 0.0;
    m[8] = s[2];  m[9] = u[2];  m[10]=-f[2];  m[11]=0.0;
    m[12]= 0.0;   m[13]= 0.0;   m[14]= 0.0;   m[15]=1.0;

    /* Update projection matrix */
    glMultMatrixf(m);
    glTranslatef(-eyeX, -eyeY, -eyeZ);

    return 0;
}

/* Own implementation of gluPerspective
 *  basically just calculates the required frustrum */
static void custom_gluPerspective(double fovY, double aspect, double zNear, double zFar)
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}


int video_initialise(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf_error("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    /* Open window */
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

    /* Create renderer (not used if using OpenGL) */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        printf_error("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return -1;
    }

    if (SDL_SetRenderDrawColor(renderer,
                VIDEO_BACKGROUND_R,
                VIDEO_BACKGROUND_G,
                VIDEO_BACKGROUND_B, 0) < 0)
    {
        printf_error("SDL_SetRenderDrawColor failed: %s\n", SDL_GetError());
        return -1;
    }

    /* Initialise OpenGL */
    context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        printf_error("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        return -1;
    }

    /* Set OpenGL flags etc. */
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glEnable(GL_DEPTH_TEST);

    video_set_perspective();

    return 0;
}

void video_destroy(void)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    /* Free SDL related stuff */
    SDL_GL_DeleteContext(context);

    /* Quit SDL
     *  (can be here as SDL_Init called in same file) */
    SDL_Quit();
}

int video_clear_screen(void)
{
    /* Don't clear if using opengl instead of renderer */
    /*if (SDL_RenderClear(renderer) < 0) return -1;*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return 0;
}

void video_present(void)
{
    SDL_GL_SwapWindow(window);
    /*SDL_RenderPresent(renderer);*/
}

int video_set_camera(void)
{
    if (custom_gluLookAt(0.0,0.0,5.0,
            0.0,0.0,0.0,
            0.0,1.0,0.0) < 0)
    {
        return -1;
    }


    return 0;
}

void video_set_ortho(void)
{
    /* Shouldn't touch projection matrix outside of this file */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-5.0,5.0, -5.0,5.0, 0.0,50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void video_set_perspective(void)
{
    /* Shouldn't touch projection matrix outside of this file */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    custom_gluPerspective(60.0, (640.0/480.0), 0.1, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

