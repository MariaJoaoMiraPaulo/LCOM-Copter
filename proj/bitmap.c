
#include <minix/drivers.h>
#include <stdlib.h>
#include <stdio.h>
#include "copter.h"
#include "vbe.h"
#include "keyboard.h"
#include "timer.h"
#include "i8254.h"
#include "KBD.h"
#include "lmlib.h"
#include "video_gr.h"
#include "GameState.h"
#include "Obstacles.h"
#include "Margins.h"
#include "mouse.h"
#include "bitmap.h"


Bitmap* loadBitmap(const char* filename) {
	// allocating necessary size
	Bitmap* bmp= (Bitmap*) malloc(sizeof(Bitmap));

	// open filename
	FILE *fileP;

	if((fileP = fopen(filename, "rb"))==NULL)
		return NULL;

	// read the bitmap file header
	Bitmap_File_Header bitmapFileHeader;
	fread(&bitmapFileHeader, 2, 1, fileP); //reads data from the given stream (fileP) to bitmapFileHeader, 1 == number of elements to be read (2 bytes)

	// verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.type != 0x4D42) {
		fclose(fileP);
		return NULL;
	}


	//continues to read data from the given stream (fileP) to bitmapFileHeader, 4 bytes each one!
	int read_result;
	do {
		if ((read_result = fread(&bitmapFileHeader.size, 4, 1, fileP)) != 1)
			break;
		if ((read_result = fread(&bitmapFileHeader.reserved, 4, 1, fileP)) != 1)
			break;
		if ((read_result = fread(&bitmapFileHeader.offset, 4, 1, fileP)) != 1)
			break;
	} while (0);

	if (read_result = !1) {
		fprintf(stderr, "Error reading file\n");
		exit(-1);
	}

	// read the bitmap info header
	BitmapInfoHeader bitmapInfoHeader;
	fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, fileP);

	// move file pointer to the begining of bitmap data
	fseek(fileP, bitmapFileHeader.offset, SEEK_SET);

	// allocate enough memory for the bitmap image data
	unsigned char* bitmapImagePointer = (unsigned char*) malloc(bitmapInfoHeader.imageSize);

	// verify memory allocation
	if (!bitmapImagePointer) {
		free(bitmapImagePointer);
		fclose(fileP);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImagePointer, bitmapInfoHeader.imageSize, 1, fileP);

	// make sure bitmap image data was read
	if (bitmapImagePointer == NULL) {
		fclose(fileP);
		return NULL;
	}

	// close file and return bitmap image data
	fclose(fileP);

	bmp->bitmapData = bitmapImagePointer;
	bmp->bitmapInfoHeader = bitmapInfoHeader;

	return bmp;
}



void drawBitmap(Bitmap* bmp, int x, int y)
{

	int width = bmp->bitmapInfoHeader.width;
	int height = bmp->bitmapInfoHeader.height;

	if (bmp == NULL)
		return;

	if (x + width < 0 || x > getHres() || y + height < 0 || y > getVres())
		return;

	unsigned char* bufferStartPos = getDoubleBuffer();
	unsigned char* imgStartPos;



	int i,pos;
	for (i=0;i<height;i++)
	{
		pos=y+height-1-i;
		imgStartPos = bmp->bitmapData + i * width*2;
		memcpy(bufferStartPos+x*2+pos*getHres()*2,imgStartPos,width*2);
	}



}

void drawBitmapWithoutBackground (Bitmap* bmp, int x, int y){


	unsigned short byte1,byte2,color;
	int width = bmp->bitmapInfoHeader.width;
	int height = bmp->bitmapInfoHeader.height;

	if (bmp == NULL)
		return;

	if (x + width < 0 || x > getHres() || y + height < 0 || y > getVres())
		return;

	unsigned char* buffer;
	unsigned char* imageStartPos= bmp->bitmapData;
	int i,j;

	for (i=0;i<height;i++){
		buffer= getDoubleBuffer()+x*2+(y+height-1-i)*getHres()*2;

		for (j=0;j<width*2;j++){

			byte1=imageStartPos[j+i*width*2];
			byte2=imageStartPos[j+i*width*2+1];
			color= (byte1 | (byte2 << 8));

			if (color!=rgb(0,255,0)){
				*buffer=imageStartPos[j+i*width*2];
				buffer++;
				*buffer=imageStartPos[j+i*width*2+1];
				j++;
				buffer++;

			}
			else{
				j++;
				buffer++;
				buffer++;

			}
		}
	}


}

void drawNumbers(Bitmap* bmp,int x,int y, char number){

	int space=20;
	int limit;
	limit=number-48;

	unsigned short byte1,byte2,color;
	int width = space;
	int height = bmp->bitmapInfoHeader.height;

	if (bmp == NULL)
		return;

	if (x + width < 0 || x > getHres() || y + height < 0 || y > getVres())
		return;

	unsigned char* buffer;
	unsigned char* imageStartPos= bmp->bitmapData+limit*space*2;
	int i,j;

	for (i=0;i<height;i++){
		buffer= getDoubleBuffer()+x*2+(y+height-1-i)*getHres()*2;

		for (j=0;j<width*2;j++){

			byte1=imageStartPos[j+i*bmp->bitmapInfoHeader.width*2];
			byte2=imageStartPos[j+i*bmp->bitmapInfoHeader.width*2+1];
			color= (byte1 | (byte2 << 8));

			if (color!=rgb(0,255,0)){
				*buffer=imageStartPos[j+i*bmp->bitmapInfoHeader.width*2];
				buffer++;
				*buffer=imageStartPos[j+i*bmp->bitmapInfoHeader.width*2+1];
				j++;
				buffer++;

			}
			else{
				j++;
				buffer++;
				buffer++;

			}
		}
	}

}


void draw_distance(int distance, Bitmap* bmp){



	//FREE IMAGES
	drawNumbers(bmp,466,530,'D');
	drawNumbers(bmp,483,530,'I');
	drawNumbers(bmp,500,530,'S');
	drawNumbers(bmp,517,530,'T');
	drawNumbers(bmp,534,530,'A');
	drawNumbers(bmp,551,530,'N');
	drawNumbers(bmp,566,530,'C');
	drawNumbers(bmp,583,530,'E');
	drawNumbers(bmp,600,530,':');

	int i=0;
	int pos;
	char t;
	while (distance > 0) {
		int digit = distance % 10;
		pos=750-i*20;
		t= (char) (digit + '0');
		drawNumbers(bmp,pos,530,t);
		distance /= 10;
		i++;
	}


}

void drawTime(char* time){

	Bitmap* teste;
	Bitmap* clock;
	teste=loadBitmap("/home/lcom/repos/proj/images/abcp.bmp");
	clock=loadBitmap("/home/lcom/repos/proj/images/clock.bmp");

	drawBitmapWithoutBackground(clock,2,10);
	drawNumbers(teste,30,2, time[0]);
	drawNumbers(teste,45,2, time[1]);
	drawNumbers(teste,60,2, ':');
	drawNumbers(teste,75,2, time[2]);
	drawNumbers(teste,90,2, time[3]);
	drawNumbers(teste,105,2, ':');
	drawNumbers(teste,120,2, time[4]);
	drawNumbers(teste,135,2, time[5]);

	deleteBitmap(teste);
	deleteBitmap(clock);




}


void deleteBitmap(Bitmap* bmp) {
	if (bmp == NULL)
		return;

	free(bmp->bitmapData);
	free(bmp);
}


