#ifndef __RTC_H
#define __RTC_H

/** @defgroup rtc Rtc
 * @{
 *
 * Module that create and control everything that is related to rtc
 *
 */

/** @name Date structure */
/** @{
 *
 * Date	 structure
 */
typedef struct{
	unsigned short seconds,minutes,hours,dayOfTheWeek, dayOfTheMonth, month,year;
}Date;
/** @} end of Date */

int combine(int a, int b) ;
int rtc_test_conf(void);
int rtc_test_date(void);
int rtc_test_int(/* to be defined in class */);
void wait_valid_rtc(void);
unsigned short readReg(int reg);

/** @} end of rtc */

#endif /* __TEST6_H */
