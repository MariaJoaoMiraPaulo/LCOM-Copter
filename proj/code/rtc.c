#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "rtc.h"
#include "RTCC.h"
#include "bitmap.h"

int rtc_test_conf(void) {
	unsigned long reg = 0;
	int ret=0;

	int counter;
	for(counter=0;counter<14;counter++){

		wait_valid_rtc();
		ret=sys_outb(RTC_ADDR_REG, counter);
		if(ret!= OK){
			printf("Error reading on register %d  !!!\n", counter);
			return 1;
		}
		ret=sys_inb(RTC_DATA_REG, &reg);
		if(ret!= OK){
			printf("Error writing on register %d  !!!\n", counter);
			return 1;
		}

		printf("Register %d: 0x%x\n",counter , reg);

	}
	return 0;
}


int rtc_test_date(void) {
	unsigned long seconds,minutes,hours,dayOfTheWeek, dayOfTheMonth, month,year;
	Date date;
	char d1,d2;

	Bitmap* teste;
	teste=loadBitmap("/home/lcom/repos/proj/images/abcb.bmp");


	//changeReg(0x11,2);
	//changeReg(RTC_REG_B,RTC_REG_B_DM);
	date.seconds=readReg(RTC_REG_SECONDS);
	date.minutes=readReg(RTC_REG_MINUTES);
	date.hours=readReg(RTC_REG_HOURS);
	date.dayOfTheWeek=readReg(RTC_REG_DAY_OF_WEEK);
	date.dayOfTheMonth=readReg(RTC_REG_DAY_OF_MONTH);
	date.month=readReg(RTC_REG_MONTH);
	date.year=readReg(RTC_REG_YEAR);

	date.hours= ((date.hours >> 4) * 10) + (date.hours & 0x0F);
	date.minutes=((date.minutes >> 4) * 10) + (date.minutes & 0x0F);
	date.seconds=((date.seconds >> 4) * 10) + (date.seconds & 0x0F);

	char time[5];

	if(date.hours<10){
		time[0]='0';
		time[1]=(date.hours+'0');

	}
	else {
		d1=((date.hours/10)+'0');
		d2=((date.hours%10)+'0');
		time[0]=d1;
		time[1]=d2;
	}


	if (date.minutes<10){
		time[2]='0';
		time[3]=(date.minutes+'0');
	}
	else{
		d1=((date.minutes/10)+'0');
		d2=((date.minutes%10)+'0');
		time[2]=d1;
		time[3]=d2;

	}

	if (date.seconds<10){
		time[4]='0';
		time[5]=(date.seconds+'0');
	}
	else{
		d1=((date.seconds/10)+'0');
		d2=((date.seconds%10)+'0');
		time[4]=d1;
		time[5]=d2;

	}

	drawTime(time);

}

int rtc_test_int(/* to be defined in class */) { 
	/* To be completed */
}

void wait_valid_rtc(void) {
	unsigned long regA = 0;
	do {

		sys_outb(RTC_ADDR_REG, RTC_REG_A);
		sys_inb(RTC_DATA_REG, &regA);

	} while ( regA & RTC_UIP);
}

unsigned short readReg(int reg){
	unsigned long retorno,ret;

	wait_valid_rtc();

	ret=sys_outb(RTC_ADDR_REG, reg);
	if(ret!= OK){
		printf("Error reading on register %d  !!!\n", reg);
		return 1;
	}
	ret=sys_inb(RTC_DATA_REG, &retorno);
	if(ret!= OK){
		printf("Error writing on register %d  !!!\n", reg);
		return 1;
	}

	return retorno;
}

int changeReg(int reg, int bit){
	unsigned long regContent;
	int ret;

	regContent=readReg(reg);

	if(regContent & RTC_REG_B_DM)
		return 0;

	ret=sys_outb(RTC_ADDR_REG, RTC_REG_B);
	if(ret!= OK){
		printf("Error reading on register %d  !!!\n", RTC_REG_B);
		return 1;
	}

	unsigned char newValue= regContent | (0x00 | (unsigned char) BIT(bit));
	ret=sys_outb(RTC_DATA_REG, newValue);

	if(ret!= OK){
		printf("Error writing on register %d  !!!\n", reg);
		return 1;
	}
	return 0;
}
