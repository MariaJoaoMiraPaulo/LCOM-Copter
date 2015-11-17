#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

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

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void *vg_init(unsigned short mode){
	struct reg86u reg86;

	reg86.u.b.intno = BIOS_VIDEO_CARD;    //initialize reg86 struc with the functions and modes pretend
	reg86.u.w.ax = SET_VBE_MODE;
	reg86.u.w.bx= LINEAR_FRAME_BUFFER|mode;

	if( sys_int86(&reg86) != OK ) {
		printf("vg_exit(): sys_int86() failed \n");
		return NULL;
	}

	vbe_mode_info_t mode_info;

	if(vbe_get_mode_info(mode,&mode_info) != OK){
		printf("vg_init(): vbe_get_mode_info() failed \n");
		return NULL;
	}

	int r;
	struct mem_range mr;

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes)(mode_info.PhysBasePtr);
	//mr.mr_size = mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel;
	mr.mr_limit = mr.mr_base +mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel;

	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, mode_info.XResolution * mode_info.YResolution * mode_info.BitsPerPixel/8);

	if(video_mem == MAP_FAILED)
		panic("video_txt couldn't map video memory");

	/* Save text mode resolution */

	h_res =mode_info.XResolution;
	v_res=mode_info.YResolution;
	bits_per_pixel=mode_info.BitsPerPixel;

	return video_mem;
}

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00;    /* Set Video Mode function */
	reg86.u.b.al = 0x03;    /* 80x25 text mode*/

	if( sys_int86(&reg86) != OK ) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}

int vg_draw(unsigned short x, unsigned short y, unsigned short size, unsigned long color){

	int i,j;
	video_mem=vg_init(0x105);


	if (x<0 || x+size>h_res || y<0 || y+size>v_res){
		return 1;
	}


	for (i=x;i<size+x;i++)
	{
		for(j=y;j<size+y;j++)
		{
			*(video_mem+((i+j*h_res)*bits_per_pixel/8))=color;
		}
	}

	return 0;
}


