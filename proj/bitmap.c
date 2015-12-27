
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


//
//void drawBitmap(Bitmap* bmp, int x, int y, Alignment alignment) {
//    if (bmp == NULL)
//        return;
//
//    int width = bmp->bitmapInfoHeader.width;
//    int drawWidth = width;
//    int height = bmp->bitmapInfoHeader.height;
//
//    if (alignment == ALIGN_CENTER)
//        x -= width / 2;
//    else if (alignment == ALIGN_RIGHT)
//        x -= width;
//
//    if (x + width < 0 || x > getHres()|| y + height < 0
//            || y > getVres())
//        return;
//
//    int xCorrection = 0;
//    if (x < 0) {
//        xCorrection = -x;
//        drawWidth -= xCorrection;
//        x = 0;
//
//        if (drawWidth > getHres())
//            drawWidth = getHres();
//    } else if (x + drawWidth >= getHres()) {
//        drawWidth = getHres() - x;
//    }
//
//    char* bufferStartPos;
//    char* imgStartPos;
//
//    int i;
//    for (i = 0; i < height; i++) {
//        int pos = y + height - 1 - i;
//
//        if (pos < 0 || pos >= getVres())
//            continue;
//
//        bufferStartPos = getDoubleBuffer();
//        bufferStartPos += x * 2 + pos * getHres() * 2;
//
//        imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;
//
//        memcpy(bufferStartPos, imgStartPos, drawWidth * 2);
//    }
//
//}

void deleteBitmap(Bitmap* bmp) {
	if (bmp == NULL)
		return;

	free(bmp->bitmapData);
	free(bmp);
}
