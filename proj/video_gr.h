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
 * @brief Draws a square frame on the screen
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_draw_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color);

/**
 * @brief Draws a square on the screen
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_draw_square_frame(unsigned short x, unsigned short y, unsigned short size,unsigned long color);

/**
 * @brief Paints a specific pixel on the screen
 *
 * @return 0 upon success, non-zero upon failure
 */

int vg_print_pixel(unsigned short x, unsigned short y, unsigned long color);

/**
 *@brief Draws a Circle on scree
 *
 *@param x coordinate x
 *@param y coordinate y
 *@param radius radius of the circle
 *@param color color of the circle
 */
 void DrawCircle(int x0, int y0, int radius,unsigned long color);
/**
 * @brief Paints the screen on black
 *
 */
void vg_screen_to_black();

/**
 * @brief copy value of double_buffer to video_mem and prints the screen to black
 *
 */
void update_screen();
/**
 * @brief returns the color on pixel (x,y)
 *
 * @param x coordinate x
 * @param y coordinate y
 */

int color(long x, long y);
/**
 * @brief returns Horizontal Resolution
 */

unsigned getHres();
/**
 * @brief returns Vertical Resolution
 */
unsigned getVres();
/**
 * @brief returns doublebuffer
 */
unsigned char* getDoubleBuffer();
/**
 * @brief returns getVideoMem
 */
unsigned char* getVideoMem();
/**
 * @brief converts color to rgb
 *
 * @param r quantity of red
 * @param g quantity of green
 * @param b quantity of blue
 */
unsigned int rgb(unsigned char r, unsigned char g, unsigned char b);


#endif /* __VIDEO_GR_H */
