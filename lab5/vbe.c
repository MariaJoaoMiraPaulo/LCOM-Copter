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

	/*if(lm_init()==NULL)
	{
		return 1;
	}*/

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

	if (r.u.w.ax != VBE_FUNC_SUPPORTED | VBE_FUNC_CALL_SUCCE)
	{
		return 1;
	}

	*vmi_p = *((vbe_mode_info_t *)map_info.virtual);

	lm_free(&map_info);

	return 0;
}

int vbe_get_mode_info_block( vbe_mode_info_t *vmi_p) {
/*
	struct reg86u r;

	if(lm_init()==NULL)
	{
		return 1;
	}

	if (lm_alloc(sizeof(vbe_mode_info_t),&map_info)==NULL)
	{
		return 1;
	}

	r.u.w.ax = GET_VBE_CONTROLLER_INFORMATION;  //initialize r struc with the functions and modes pretend
	r.u.w.es = PB2BASE(map_info.phys);
	r.u.w.di = PB2OFF(map_info.phys);
	r.u.b.intno = BIOS_VIDEO_CARD;

	if( sys_int86(&r) != OK ) {
		printf("vbe_get_mode_info(): sys_int86() failed \n");
		return 1;
	}

	if (r.u.w.ax != VBE_FUNC_SUPPORTED | VBE_FUNC_CALL_SUCCE)
	{
		return 1;
	}

*/

}
