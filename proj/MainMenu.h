#ifndef __MAINMENU_H
#define __MAINMENU_H

#include "mouse.h"
#include "Button.h"

typedef struct {
	MouseInfo mouse;
	Button b1;
	Button b2;
	Button b3;
	Bitmap* menuImage;
} MainMenu;

typedef struct {
	MouseInfo mouse;
	Button b1;
	Button b2;
	Button b3;
	Bitmap* menuImage;
} MenuGameOver;

typedef struct {
	MouseInfo mouse;
	Button b1;
	Button b2;
	Button b3;
	Bitmap* menuImage;
} OptionMenu;

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
 * @brief deals with main menu timer interrupt
 *
 * @param mM struct to get informations
 *
 * @return 0 if is to end the cycle
 */
int mainMenuTimerInt(MainMenu* mM);

/*
 * @brief will be the core of main menu
 */
int mainMenu();

/**
 *@brief Functions that will act like a constructor, initializing members of menu game over struct
 */
MenuGameOver* menuGameOverInit();

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

/**
 *@brief Functions that will act like a constructor, initializing members of option menu struct
 */
OptionMenu* optionMenuInit();

/*
 * @brief Functions that deletes struct option menu and all of is members
 *
 * @param oM struct to be deleted
 */
void  optionMenuDestructor(OptionMenu* oM);

/*
 * @brief option menu
 */
int optionMenu();

/*
 * @brief reset all mouse config
 *
 * @param mouse mouse to be reseted
 */
void resetMouse(MouseInfo* mouse);





#endif /* __VBE_H */
