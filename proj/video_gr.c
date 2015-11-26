#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include "sprite.h"
#include "pixmap.h"

#include "vbe.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xF0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem; /* Process address to which VRAM is mapped */
static char *double_buffer;

static unsigned h_res; /* Horizontal screen resolution in pixels */
static unsigned v_res; /* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void *vg_init(unsigned short mode) {
	struct reg86u reg86;

	reg86.u.b.intno = BIOS_VIDEO_CARD; //initialize reg86 struc with the functions and modes pretend
	reg86.u.w.ax = SET_VBE_MODE;
	reg86.u.w.bx = LINEAR_FRAME_BUFFER | mode;

	if (sys_int86(&reg86) != OK) {
		printf("vg_exit(): sys_int86() failed \n");
		return NULL;
	}

	vbe_mode_info_t mode_info;

	if (vbe_get_mode_info(mode, &mode_info) != OK) {
		printf("vg_init(): vbe_get_mode_info() failed \n");
		return NULL;
	}

	int r;
	struct mem_range mr;

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes)(mode_info.PhysBasePtr);
	//mr.mr_size = mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel;
	mr.mr_limit = mr.mr_base
			+ mode_info.XResolution * mode_info.YResolution
			* mode_info.BitsPerPixel;

	if ( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *) mr.mr_base,
			mode_info.XResolution * mode_info.YResolution
			* mode_info.BitsPerPixel / 8);

	if (video_mem == MAP_FAILED)
		panic("video_txt couldn't map video memory");

	/* Save text mode resolution */

	h_res = mode_info.XResolution;
	v_res = mode_info.YResolution;
	bits_per_pixel = mode_info.BitsPerPixel;

	double_buffer=malloc(h_res*v_res*bits_per_pixel/8);

	return video_mem;
}

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00; /* Set Video Mode function */
	reg86.u.b.al = 0x03; /* 80x25 text mode*/

	free(double_buffer);

	if (sys_int86(&reg86) != OK) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}

int vg_draw_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {

	int i, j;
	video_mem = vg_init(MODE_105);

	if (x < 0 || x + size > h_res || y < 0 || y + size > v_res) {
		return 1;
	}

	for (i = x; i < size + x; i++) {
		*(video_mem + ((i + y * h_res) * bits_per_pixel / 8)) = color;
		*(video_mem + ((i + (y + size) * h_res) * bits_per_pixel / 8)) = color;
	}

	for (i = y; i < size + y; i++) {
		*(video_mem + ((x + i * h_res) * bits_per_pixel / 8)) = color;
		*(video_mem + (((x + size) + i * h_res) * bits_per_pixel / 8)) = color;
	}

	return 0;
}

int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {
	//double m,b;
	float m, b;
	unsigned short i, j, tempx, tempy;
	int length;

	video_mem = vg_init(MODE_105);

	//test limits of coordinates, i will not test that the coordinates are <0 because they are unsigned short

	if (xi > h_res)
		xi = h_res - 1;

	if (xf > h_res)
		xf = h_res - 1;

	if (yi > v_res)
		yi = v_res - 1;

	if (yf > v_res)
		yf = v_res - 1;

	//to know what where we start to draw line
	if (yi > yf) {
		tempy = yf;
		tempx = xf;
		xf = xi;
		yf = yi;
		xi = tempx;
		yi = tempy;
	}

	//horizontal line
	if (yi == yf) {
		if (xi < xf)
			length = xf - xi;
		else
			length = xi - xf;

		i = xi;
		while (length > 0) {
			*(video_mem + ((i + yi * h_res) * bits_per_pixel / 8)) = color;
			if (xi < xf)
				i++;
			else
				i--;
			length--;
		}
	} else if (xi == xf) {   //vertical line
		i = yi;
		while (i <= yf) {
			*(video_mem + ((xi + i * h_res) * bits_per_pixel / 8)) = color;
			i++;
		}
	} else if (yf > yi) {
		m = ((float) (yf - yi)) / (xf - xi);
		b = ((float) yi - ((float) m * xi));
		i = xi;
		j = yi;
		if (m > 1) { //slope is greater than 1, so y will change value faster than x
			while (j <= yf) {
				*(video_mem + ((i + j * h_res) * bits_per_pixel / 8)) = color;
				j++;
				i = trunc(((float) (j - b)) / m);
			}
		} else if (m > 0 && m < 1) { //slope is between 1 and 0, so x will change value faster than y
			while (i <= xf) {
				*(video_mem + ((i + j * h_res) * bits_per_pixel / 8)) = color;
				i++;
				j = trunc(((float) (m * i)) + b);
			}
		} else if (m < 0 && m < -1) { //slope is smaller than -1, so y will change value faster than x
			while (j <= yf) {
				*(video_mem + ((i + j * h_res) * bits_per_pixel / 8)) = color;
				j++;
				i = trunc(((float) (j - b)) / m);
			}
		} else if (m < 0 && m > -1) { //slope between 0 and -1, so x will change value faster than y
			while (i >= xf) {
				*(video_mem + ((i + j * h_res) * bits_per_pixel / 8)) = color;
				i--;
				j = trunc(((float) (m * i)) + b);
			}
		} else if (m == 1 || m == -1) { //inclination is 45 degrees so x and y change value at same time
			while (j <= yf) {
				*(video_mem + ((i + j * h_res) * bits_per_pixel / 8)) = color;
				if (m == 1)
					i++;
				else
					i--;
				j++;
			}
		}
	}

	return 0;
}

int vg_print_pixel(unsigned short x, unsigned short y, unsigned long color) {

	if (x > h_res || y > v_res)
		return 1;

	*(double_buffer+((x+h_res*y)*bits_per_pixel/8))=color;
	//*(video_mem+((x+h_res*y)*bits_per_pixel/8))=color;

	return 0;

}

int vg_draw_xpm(unsigned short x, unsigned short y, unsigned short width,
		unsigned short height, char *map) {

	if (x + width > h_res || y + height > v_res) {
		return 1;
	}

	int i, j;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			vg_print_pixel(x + i, y + j, *(map + (i + j * width) * bits_per_pixel / 8));
		}
	}

	return 0;
}

void vg_screen_to_black(){
	int i, j;
	for (i = 0; i < h_res; i++)
	{
		for (j = 0; j < v_res; j++)
		{
			vg_print_pixel(i,j,0);
		}
	}

}

/*void vg_print_screen(unsigned short color){
	mem_set(double_buffer,color,h_res*v_res*bits_per_pixel/8);
}*/

void update_screen(){
	memcpy(video_mem,double_buffer,h_res*v_res*bits_per_pixel/8);
	vg_screen_to_black();
	//vg_print_screen(0);
}

/*int vg_draw_sprite(Sprite *image) {

}*/
