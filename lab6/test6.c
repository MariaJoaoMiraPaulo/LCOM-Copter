#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "test6.h"
#include "RTC.h"

int rtc_test_conf(void) {
	unsigned long reg = 0;
	int ret=0;

	printf("\tRTC\n\n");

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

	//changeReg(0x11,2);
	//changeReg(RTC_REG_B,RTC_REG_B_DM);
	date.seconds=readReg(RTC_REG_SECONDS);
	date.minutes=readReg(RTC_REG_MINUTES);
	date.hours=readReg(RTC_REG_HOURS);
	date.dayOfTheWeek=readReg(RTC_REG_DAY_OF_WEEK);
	date.dayOfTheMonth=readReg(RTC_REG_DAY_OF_MONTH);
	date.month=readReg(RTC_REG_MONTH);
	date.year=readReg(RTC_REG_YEAR);

	switch(date.dayOfTheWeek){
	case 0:
		printf("Sunday,  ");
		break;
	case 1:
		printf("Monday,  ");
		break;
	case 2:
		printf("Tuesday,  ");
		break;
	case 3:
		printf("Wednesday,  ");
		break;
	case 4:
		printf("Thursday,  ");
		break;
	case 5:
		printf("Friday,  ");
		break;
	case 6:
		printf("Saturday,  ");
		break;
	default :
		printf("Error,  ");
	}

	printf("%x /",date.dayOfTheMonth);

	if(date.month<10)
		printf(" 0%x /",date.month);
	else printf(" %x /",date.month);

	if(date.year<10)
		printf(" 200%x   ",date.year);
	else printf(" 20%x   ",date.year);

	if(date.hours<10)
		printf("0%x:",date.hours);
	else printf("%x:",date.hours);

	if(date.minutes<10)
		printf("0%x:",date.minutes);
	else printf("%x:",date.minutes);

	if(date.seconds<10)
		printf("0%x\n",date.seconds);
	else printf("%x\n",date.seconds);



	//printf("%x:%x:%x\n",hours,minuts,seconds);

	return 0;

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
