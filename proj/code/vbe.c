#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <stdlib.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {
	struct reg86u r;
	mmap_t map_info;

	if(lm_init()==NULL)
	{
		return 1;
	}

	if (lm_alloc(sizeof(vbe_mode_info_t),&map_info)==NULL)
	{
		return 1;
	}

	r.u.w.ax = GET_VBE_MODE_INFORMATION;  //initialize r struc with the functions and modes pretend
	r.u.w.es = PB2BASE(map_info.phys);
	r.u.w.di = PB2OFF(map_info.phys);
	r.u.w.cx = mode;
	r.u.b.intno = BIOS_VIDEO_CARD;

	if( sys_int86(&r) != OK ) {
		printf("vbe_get_mode_info(): sys_int86() failed \n");
		return 1;
	}

	if(r.u.b.al != VBE_FUNC_SUPPORTED)
		return 1;

	if(r.u.b.ah != VBE_FUNC_CALL_SUCCE)
		return 1;

	if(r.u.b.ah == VBE_FUNC_CALL_FAILED)
		return 1;

	if(r.u.b.ah == VBE_FUNC_NOT_SUPPORTED)
		return 1;

	if(r.u.b.ah == VBE_FUNC_CALL_INVALID)
		return 1;


	*vmi_p = *((vbe_mode_info_t *)map_info.virtual);

	lm_free(&map_info);

	return 0;
}

int vbe_get_mode_info_block( vbe_info_block *vmi_p) {

	struct reg86u r;
	mmap_t map_info;

	/*if(lm_init()==NULL)
	{
		return 1;
	}*/

	vmi_p=lm_alloc(sizeof(vbe_info_block),&map_info);
	if(vmi_p==NULL){
		return 1;
	}

	vmi_p->signature[0]='V';
	vmi_p->signature[1]='B';
	vmi_p->signature[2]='E';
	vmi_p->signature[3]='2';

	r.u.w.ax = GET_VBE_CONTROLLER_INFORMATION;  //initialize r struc with the functions and modes pretend
	r.u.w.es = PB2BASE(map_info.phys);
	r.u.w.di = PB2OFF(map_info.phys);
	r.u.b.intno = BIOS_VIDEO_CARD;

	if( sys_int86(&r) != OK ) {
		printf("vbe_get_mode_info_block(): sys_int86() failed \n");
		return 1;
	}

	if(r.u.b.al != VBE_FUNC_SUPPORTED)
		return 1;

	if(r.u.b.ah != VBE_FUNC_CALL_SUCCE)
		return 1;

	if(r.u.b.ah == VBE_FUNC_CALL_FAILED)
		return 1;

	if(r.u.b.ah == VBE_FUNC_NOT_SUPPORTED)
		return 1;

	if(r.u.b.ah == VBE_FUNC_CALL_INVALID)
		return 1;

	print_info(vmi_p);
	lm_free(&map_info);

	return 0;

}

void print_info(vbe_info_block *mode_info){
	if(mode_info->capabilities[0] & DAC_CAPABILITIES){
		printf("\nDAC width is switchable to 8 bits per primary color");
	}
	else {
		printf("\nDAC is fixed width, with 6 bits per primary color");
	}

	if(mode_info->capabilities[0] & VGA_CAPABILITIES){
		printf("\nController is not VGA compatible");
	}
	else {
		printf("\nController is VGA compatible");
	}

	if(mode_info->capabilities[0] & RAMDAC_CAPABILITIES){
		printf("\nWhen programming large blocks of information to the RAMDAC,use the blank bit in Function 09h");
	}
	else {
		printf("\nNormal RAMDAC operation");
	}

	/*unsigned short * p;
	printf("\tModes: \n");
	for (p = (unsigned short *)mode_info->videoModePtr; *p !=(unsigned)-1; p++)
	{
		printf("\n 0x%3x", *p);
	}*/

	printf("\n\nTotal Memory: %d\n", mode_info->totalMemory*64);
}
