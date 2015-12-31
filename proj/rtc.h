#ifndef __RTC_H
#define __RTC_H




typedef struct{
	unsigned short seconds,minutes,hours,dayOfTheWeek, dayOfTheMonth, month,year;
}Date;

//typedef struct {
//
//	unsigned short x, y, width, height;
//	int distance;
//	//imagem
//
//}Copter;

int combine(int a, int b) ;
int rtc_test_conf(void);
int rtc_test_date(void);
int rtc_test_int(/* to be defined in class */);
void wait_valid_rtc(void);
unsigned short readReg(int reg);

#endif /* __TEST6_H */
