#ifndef __MARGINS_H
#define __MARGINS_H

typedef struct {
	unsigned short x,y,width,height;
} Margin;

Margin* newMargin(unsigned short x, unsigned short y, unsigned short width, unsigned short height);

void draw_margin(Margin** margin);





















#endif /* __MARGINS_H */
