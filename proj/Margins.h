#ifndef __MARGINS_H
#define __MARGINS_H

typedef struct {
	int x,y,width,height;
} Margin;

Margin* newMargin(int x, int y, int width, int height);

void draw_margin(Margin** margin);





















#endif /* __MARGINS_H */
