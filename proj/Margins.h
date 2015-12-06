#ifndef __MARGINS_H
#define __MARGINS_H

typedef struct {
	short x,y;
	short width,height;
	unsigned short distanceToOtherMargin;
	unsigned short totallyPrinted;  //if the margin is totally printed this variable will be equal to 1
} Margin;

typedef enum{
	FIRST_MARGIN_OF_THE_BREAK, REST_OF_MARGINS_AT_THE_BREAK
}GenerationState;

Margin* newMargin(short x, short y, short width, short height);

void delete_margin(Margin** margins,unsigned short *sizeOfArray);

unsigned int tubeSize(unsigned int time);

void draw_margin(Margin** margins,unsigned short *sizeOfArray,unsigned int time);

int numberGeneration(int x1,int x2);

Margin* randomMargin(short x,short y,unsigned int time);

int isTotallyPrinted(Margin* margin);

void pullToTheLeft(Margin** margins, unsigned short *sizeOfArray,unsigned int time);























#endif /* __MARGINS_H */
