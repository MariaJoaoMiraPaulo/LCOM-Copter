#ifndef __RTC_CONSTANTES_H
#define __RTC_CONSTANTES_H

#define BIT(n) (0x01<<(n))

#define RTC_ADDR_REG 0x70  //to write

#define RTC_DATA_REG 0x71  //to read

#define RTC_REG_A 0x10

#define RTC_REG_B 0x11

#define RTC_UIP BIT(7)

#define OK 0

#define RTC_REG_SECONDS 0

#define RTC_REG_MINUTES 2

#define RTC_REG_HOURS 4

#define RTC_REG_DAY_OF_WEEK 6

#define RTC_REG_DAY_OF_MONTH 7

#define RTC_REG_MONTH 8

#define RTC_REG_YEAR 9

#define RTC_REG_B_DM BIT(2)

#define RTC_REG_B_24_12 BIT(1)



#endif /* __RTC_H */
