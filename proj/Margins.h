#ifndef __MARGINS_H
#define __MARGINS_H

typedef struct {
	unsigned short x,y,width,height;
	unsigned short totallyPrinted;  //if the margin is totally printed this variable will be equal to 1
} Margin;

Margin* newMargin(unsigned short x, unsigned short y, unsigned short width, unsigned short height);

void draw_margin(Margin** margin);

Margin* randomMargin(unsigned short x, unsigned short y);

int is_totallyPrinted(Margin* margin);

void pullToTheLeft(Margin** margins, unsigned short *sizeOfArray);























#endif /* __MARGINS_H */
