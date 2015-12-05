#ifndef __TEST6_H
#define __TEST6_H


typedef struct{
	unsigned short seconds,minutes,hours,dayOfTheWeek, dayOfTheMonth, month,year;
}Date;

typedef struct {

	unsigned short x, y, width, height;
	int distance;
	//imagem

}Copter;

int rtc_test_conf(void);
int rtc_test_date(void);
int rtc_test_int(/* to be defined in class */);
void wait_valid_rtc(void);
unsigned short readReg(int reg);

#endif /* __TEST6_H */
