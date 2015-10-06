#include <minix/drivers.h>
#include <sys/video.h>
#include <sys/mman.h>

#include <assert.h>

#include "vt_info.h"

#include "video_txt.h"

/* Private global variables */

static char *video_mem;		/* Address to which VRAM is mapped */

static unsigned scr_width;	/* Width of screen in columns */
static unsigned scr_lines;	/* Height of screen in lines */


void vt_fill(char ch, char attr)
{
  char *vptr;
  
  vptr=video_mem;  //vptr is pointing to the first pixel of the screen
  
  int i;
 for (i=0; i<(scr_width*scr_lines);i++)   // scr_width*scr_lines represents all the pixels
 {
	  *vptr=ch;    //modify the first byte of the pixel
	  vptr++;
	  *vptr=attr;   //modify the second byte of the pixel
	  vptr++;
 }
}

void vt_blank()
{
	vt_fill(0x00, 0x00);     //Fills the screen with blank
}

int vt_print_char(char ch, char attr, int r, int c)
{
	 char *vptr;

	 if (r>24 || c>79)
	 {
		 return 1;
	 }

	 vptr=video_mem;     //vptr is pointing to the first pixel of the screen

	 vptr= 2*c+vptr;           //goes to the right column
	 vptr= 2*r*scr_width+vptr;   //goes to the right line, now is in the right position

	 *vptr=ch;      //lets change the char
	 vptr++;
	 *vptr=attr;    //and the color of the char and the color of the background
	 vptr++;

	  return 0;
}

int vt_print_string(char *str, char attr, int r, int c)
{
	int lenOfString = strlen(str);  //initialize string length
	int enoughSpace;

	enoughSpace = (scr_width*scr_lines-(r*scr_width+c))  - lenOfString;  //calculate if the string have enough room in the image

	if (enoughSpace < 0 || r< 0 || c<0)   //if the string have no space our is put in a invalid position
		return 1;                         //the program does not do anything

	int i;
	for (i=0; i<lenOfString ;i++)      //cycle that writes on the screen
	{
		vt_print_char(str[i] , attr , r , c);  //prints char by char

		if ( c == scr_width )             //here the function see if the columns are running out
		{
			c=0;                   //if the are we change line
			r++;
		}
		else
			c++;                   //our we change column
	}

	return 0;
}

int vt_print_int(int num, char attr, int r, int c)
{
	int numLength=0, copyNum=num;

	while(copyNum > 1)         //lets see length of the integer
	{
		copyNum=copyNum/10;
		numLength++;
	}

	char str[numLength];      //create the string that will receive the converted int

	sprintf(str, "%d", num);    //str receives int like an array of chars

	if (vt_print_string(str, attr,r ,c)==0) //print the integer and see if the print was successful
		return 0;
	else
		return 1;
}


int vt_draw_frame(int width, int height, char attr, int r, int c)
{
	int lastLine=r-1+height, lastColumn=c-1+width;

	if (lastColumn> scr_width )
		return 1;

	if (lastLine>scr_lines)
		return 1;

	if  (width <=0 || height <= 0)
		return 1;

	if (width>1 && height>1)
	{
		vt_print_char(0xc9, attr, r, c);
		vt_print_char(0xbb, attr, r, lastColumn);
		vt_print_char(0xc8, attr, lastLine, c);
		vt_print_char(0xbc, attr, lastLine, lastColumn);
	}
	else if (height==1)
			vt_print_char(0xcd, attr, r, c);
	else if (width==1)
			vt_print_char(0xba, attr, r, c);

	if (width>1)
	{
		int i;
		for (i=1;i<=width-2;i++)
			{
				vt_print_char(0xcd, attr, r , c+i);
				vt_print_char(0xcd, attr, lastLine , c+i);
			}
	}

	if(height>1)
	{
		int i;
		for (i=1; i<=height-2;i++)
		{
			vt_print_char(0xba, attr, r+i , c);
			vt_print_char(0xba, attr, r+i , lastColumn);
		}

	}

	return 0;
}

/*
 * THIS FUNCTION IS FINALIZED, do NOT touch it
 */

char *vt_init(vt_info_t *vi_p) {

  int r;
  struct mem_range mr;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes)(vi_p->vram_base);
  mr.mr_limit = mr.mr_base + vi_p->vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	  panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vi_p->vram_size);

  if(video_mem == MAP_FAILED)
	  panic("video_txt couldn't map video memory");

  /* Save text mode resolution */

  scr_lines = vi_p->scr_lines;
  scr_width = vi_p->scr_width;

  return video_mem;
}
