#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include "sprite.h"
#include "pixmap.h"
#include "KBD.h"

#include "vbe.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */

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

unsigned getVideoMemSize(){
	return v_res*h_res*2;
}


unsigned int rgb(unsigned char r, unsigned char g, unsigned char b){

	//	if(r < 0 || r > 255 || g<0 || g > 255 || b < 0 || b > 255)
	//		return -1;
	//
	//	int red=r*31/255;
	//	int green= g*63/255;
	//	int blue= b*31/255;
	//
	//	return (red << 11) | (green << 5) | blue;

	return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);

}


int vg_print_pixel(unsigned short x, unsigned short y, unsigned int color) {

	if (x > h_res || y > v_res)
		return 1;

	char colorByte1, colorByte2;

	colorByte1 = color & 0xFF;

	colorByte2 = (color >> 8) & 0xFF;


	double_buffer[(x+h_res*y)*bits_per_pixel/8]=colorByte1;
	double_buffer[(x+h_res*y)*bits_per_pixel/8+1]=colorByte2;

	return 0;


}


void DrawCircle(int x0, int y0, int radius, unsigned long color)
{

int i,j;

for( i=-radius; i<=radius; i++)
	for( j=-radius; j<=radius; j++)
		if(j*j+i*i <= radius*radius)
			 vg_print_pixel(x0+j, y0+i,color);

}


int vg_draw_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color){

	int i, j;

	if (x < 0 || x + size > h_res || y < 0 || y + size > v_res) {
		return 1;
	}

	for (i = x; i < size + x; i++) {
		vg_print_pixel(i,y,color);
		vg_print_pixel(i,y+size,color);
	}
	for(i = y; i< size+y;i++){
		vg_print_pixel(x,i,color);
		vg_print_pixel(x+size,i,color);
	}
	/*
	for (i = x; i < size + x; i++) {
		for (j = y; j < size + y; j++) {
			vg_print_pixel(i,j,color);
		}
	}*/

	return 0;


}


int vg_draw_square_frame(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {

	int i, j;

	if (x < 0 || x + size > h_res || y < 0 || y + size > v_res) {
		return 1;
	}

	for (i = x; i < size + x; i++) {
		vg_print_pixel(i,y,color);
		vg_print_pixel(i,y+size,color);
	}

	for (i = y; i < size + y; i++) {
		vg_print_pixel(x,i,color);
		vg_print_pixel(x+size,i,color);
	}


	return 0;
}


void vg_screen_to_black(){
	int i, j;
	for (i = 0; i < h_res; i++)
	{
		for (j = 0; j < v_res; j++)
		{
			vg_print_pixel(i,j,rgb(0,0,0));
		}
	}

}

void update_screen(){
	memcpy(video_mem,double_buffer,h_res*v_res*bits_per_pixel/8);
	vg_screen_to_black();
}

unsigned getHres(){
	return h_res;
}

unsigned getVres(){
	return v_res;
}

unsigned char* getDoubleBuffer(){
	return double_buffer;
}

unsigned char* getVideoMem(){
	return video_mem;
}

int color(long x, long y){

	//
	//	unsigned long color = 0;
	//	color|= double_buffer[(x+h_res*y)*bits_per_pixel/8] & 0xFF;
	//	color|=( (double_buffer[(x+h_res*y)*bits_per_pixel/8+1] & 0xFF) << 8);
	//	return color;
	//

	if (x < 0 || y < 0 || x >= getHres() || y >= getVres())
		return -1;

	int id = (x + y * getHres()) * bits_per_pixel/8;

	unsigned short color = 0;
	color |= video_mem[id] & 0xFF;
	color |= (video_mem[id + 1] & 0xFF) << 8;

	return color;


}



