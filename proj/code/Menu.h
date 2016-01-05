#ifndef __MENU_H
#define __MENU_H

/** @defgroup menu Menu
 * @{
 *
 * Module that create and control everything that is related to subscribes and unsubscribes
 *
 */

unsigned long IRQ_SET_KBD;
int IRQ_SET_TIMER;
unsigned long IRQ_SET_MOUSE;

/*
 * @brief Functions used to subscribe all interruptions need in this program
 */
void subscribe();

/*
 * @brief Functions used to unsubscribe all interruptions need in this program
 */
void unsubscribe();

/**
 * @brief load all images of the game
 */
void loadAllImages();

/**
 * @brief delets all images of the game
 */
void DeleteAllImages();
/** @} end of Menu */

#endif /* __MENU_H */

