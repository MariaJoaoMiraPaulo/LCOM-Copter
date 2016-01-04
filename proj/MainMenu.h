#ifndef __MAINMENU_H
#define __MAINMENU_H

#include "mouse.h"
#include "Button.h"

typedef struct {
	MouseInfo mouse;
	Button b1;
	Button b2;
	Button b3;
	Button b4;
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
	Button b4;
	Button b5;
	Button b6;
	Button b7;
	Bitmap* menuImage;
	Bitmap* check;
} OptionMenu;

typedef struct {
	MouseInfo mouse;
	Button b1;
	Bitmap* menuImage;
} CreditsMenu;

typedef enum{
	SHOW_CHECK, NO_CHECK
}CheckState;

typedef enum{
	MAIN_MENU, OPTION_MENU, GAME_OVER_MENU, CREDITS_MENU
}ProgramState;

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
//int mainMenu();

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
 * @brief deals with game over menu timer interrupt
 *
 * @param mGO struct to get informations
 *
 * @return 0 if is to end the cycle
 */
int menuGameOverTimerInt(MenuGameOver* mGO, int* ret);

///*
// * @brief gameOver menu
// */
//int gameOver();

/**
 *@brief Functions that will act like a constructor, initializing members of option menu struct
 */
OptionMenu* optionMenuInit();

/*
 * @brief Function that deletes struct option menu and all of is members
 *
 * @param oM struct to be deleted
 */
void  optionMenuDestructor(OptionMenu* oM);

/*
 * @brief deals with option menu timer interrupt
 *
 * @param oM struct to get informations
 *
 * @return 0 if is to end the cycle
 */
int optionMenuTimerInt(OptionMenu* oM,int time);

/*
 * @brief option menu
 */
//int optionMenu();

/*
 * @brief Function that will act like a constructor, initializing members of credits menu struct
 */
CreditsMenu* creditsMenuInit();

/*
 * @brief Functions that deletes struct credits menu and all of is members
 *
 * @param cM struct to be deleted
 */
void creditsMenuDestructor(CreditsMenu* cM);

/*
 * @brief deals with option menu timer interrupt
 *
 * @param cM struct to get informations
 *
 * @return 0 if is to end the cycle
 */
int creditsMenuTimerInt(CreditsMenu* cM);

/*
 * @brief reset all mouse config
 *
 * @param mouse mouse to be reseted
 */
void resetMouse(MouseInfo* mouse);

/*
 * @brief the heart of the program
 */
int runningProgram();

/*
 * @brief destruct all menus
 */
void menusDestructor();





#endif /* __VBE_H */
