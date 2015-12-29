#include <minix/drivers.h>
#include <stdlib.h>
#include <stdio.h>

#include "Singleplayer.h"
#include "video_gr.h"
#include "vbe.h"
#include "Menu.h"

int main() {

	/* Initialize service */

	sef_startup();

	time_t t;
	srand((unsigned) time(&t));

	subscribe();
	vg_init(MODE_114);

	playingGame();

	unsubscribe();
	vg_exit();

	return 0;


 }
