#ifndef __MAINMENU_H
#define __MAINMENU_H

#include "mouse.h"
#include "Button.h"

typedef struct {
	MouseInfo mouse;
	Button b1;
	Button b2;
	Bitmap* menuImage;
} MainMenu;

typedef struct {
	MouseInfo mouse;
	Button b1;
	Button b2;
	Bitmap* menuImage;
} MenuGameOver;

/*
 * @brief Functions that will act like a constructor, initializing members of main menu struct
 */
MainMenu* mainMenuInit();

/*
 * @brief Functions that deletes struct main menu and all of is members
 *
 * @param sp struct to be deleted
 */
void mainMenuDestructor(MainMenu* mM);

/*
 * @brief will be the core of main menu
 */
int mainMenu();
/**
 *@brief Functions that will act like a constructor, initializing members of menu game over struct
 */
MenuGameOver* MenuGameOverInit();
/*
 * @brief Functions that deletes struct menu GameOver and all of is members
 *
 * @param sp struct to be deleted
 */
void  menuGameOverDestructor(MenuGameOver* mM);
/*
 * @brief gameOver menu
 */
int gameOver();






#endif /* __VBE_H */
