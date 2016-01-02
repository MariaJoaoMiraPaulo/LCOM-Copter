#ifndef __MENU_H
#define __MENU_H


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

void loadAllImages();

void DeleteAllImages();








#endif /* __MENU_H */

