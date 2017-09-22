#ifndef VIDEO_H__
#define VIDEO_H__

#include <SDL2/SDL.h>

#define WINDOW_TITLE "Grid Path Finding"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define VIDEO_BACKGROUND_R 0
#define VIDEO_BACKGROUND_G 0
#define VIDEO_BACKGROUND_B 0 

/* Function: video_initialise
 * --------------------
 * creates the SDL window, and sets up OpenGL
 *
 * returns: <0 on error
 */
int video_initialise(void);

/* Function: video_destroy
 * -----------------------
 * frees up resources used for video
 */
void video_destroy(void);

/* Function: video_clear_screen
 * ----------------------------
 * clears the screen
 * 
 * returns: <0 on error
 */
int video_clear_screen(void);

/* Function: video_present
 * -----------------------
 * presents the window to be rendered
 */
void video_present(void);

/* Function: video_set_camera
 * --------------------------
 * translates and rotates camera as required
 *
 * returns: <0 on error
 */
int video_set_camera(void);

/* Function: video_set_ortho
 * -------------------------
 * sets the camera to use an orthographic projection
 */
void video_set_ortho(void);

/* Function: video_set_perspective
 * -------------------------------
 * sets the camera to use a perspective projection
 */
void video_set_perspective(void);

#endif

