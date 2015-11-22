#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 *
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

/**
* @brief Draws a square on the screen
*
* @return 0 upon success, non-zero upon failure
*/
int vg_draw_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color);

/**
* @brief Paints a specific pixel on the screen
*
* @return 0 upon success, non-zero upon failure
*/
int vg_print_pixel(unsigned short x, unsigned short y, unsigned long color);

/**
 * @brief Draws a specific xpm on the screen
 *
 * @param x x coordinate of upper left corner
 * @param y y coordinate of upper left corner
 * @param width horizontal size of xpm
 * @param height vertical size of xpm
 * @param pixmap xpm to be draw
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_draw_xpm(unsigned short x, unsigned short y,unsigned short width,unsigned short height, char *pixmap);

/**
 * @brief Paints the screen on black
 *
 */
void vg_screen_to_black();

//int vg_draw_sprite(Sprite *image);
 
#endif /* __VIDEO_GR_H */
