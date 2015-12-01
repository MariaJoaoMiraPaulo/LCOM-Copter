#ifndef __MARGINS_H
#define __MARGINS_H

typedef struct {
	short x,y;
	short width,height;
	unsigned short totallyPrinted;  //if the margin is totally printed this variable will be equal to 1
} Margin;

Margin* newMargin(short x, short y, short width, short height);

void delete_margin(Margin** margins,unsigned short *sizeOfArray);

void draw_margin(Margin** margins,unsigned short *sizeOfArray);

Margin* randomMargin(short x,short y);

int is_totallyPrinted(Margin* margin);

void pullToTheLeft(Margin** margins, unsigned short *sizeOfArray);























#endif /* __MARGINS_H */
