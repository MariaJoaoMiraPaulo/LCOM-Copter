#include <minix/drivers.h>
#include <stdlib.h>
#include <stdio.h>

#include "Singleplayer.h"
#include "video_gr.h"
#include "vbe.h"
#include "Menu.h"
#include "MainMenu.h"
#include "mouse.h"
#include "bitmap.h"
#include "copter.h"


#include "Margins.h"

int bestScore;

int main() {

	/* Initialize service */

	sef_startup();

	time_t t;
	srand((unsigned) time(&t));

	subscribe();
	configure_environment();
	loadHighScore();
	vg_init(MODE_114);
	loadAllImages();


	mainMenu();
	//playingGame();
	saveHighScore();
	unsubscribe();
	DeleteAllImages();

	vg_exit();

	return 0;


}
