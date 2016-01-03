#include <minix/drivers.h>
#include "Margins.h"
#include "video_gr.h"
#include "KBD.h"

void firstImage(){
	unsigned hres = getHres();

	vg_draw_rectangle(0,0,hres,80, MARGINS_COLOR );
	vg_draw_rectangle(0,520,hres,80, MARGINS_COLOR);
}

void drawMargin() {

		unsigned hres = getHres();

		//two constant margins
	vg_draw_rectangle(0,0,hres,80, MARGINS_COLOR );
	vg_draw_rectangle(0,520,hres,80, MARGINS_COLOR);

	//updating margins
	vg_updating_double();


}

