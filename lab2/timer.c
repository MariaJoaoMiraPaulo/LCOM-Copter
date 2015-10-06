#include <minix/syslib.h>
#include <minix/drivers.h>

int timer_set_square(unsigned long timer, unsigned long freq) {

	return 1;
}

int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned long timer, unsigned char *st) {

	char command=0;
	int ret;

	command = command|TIMER_RB_CMD; //put 1 at the last two bits (bit 6 and bit 7)

	switch (timer)
	{
	case 0:
		command=command |TIMER_RB_SEL(0);  //if is the first timer put 1 at bit 1
		break;
	case 1:
		command=command |TIMER_RB_SEL(1); //if is the first timer put 1 at bit 2
	case 1:
		command=command |TIMER_RB_SEL(2); //if is the first timer put 1 at bit 3
	}

	ret=  sys_outb(TIMER_CTRL,command);   //put command on control (0x43)
	unsigned long res;

	if (ret !=0 ) //error
		return 1;

	switch (timer)
	{
	case 0:
		ret= sys_inb(TIMER_0,res);  //put config on first timer
		break;
	case 1:
		ret= sys_inb(TIMER_1,res); //put config on second timer
	case 1:
		ret= sys_inb(TIMER_2,res); //put config on  third timer
	}


	if(ret!=0)  //error
		return 1;

	*st=res;

	return 0;
}

int timer_display_conf(unsigned char conf) {

	printf("BCD : %d", 0x01 & conf);  //test bit 0

	printf("Programmed Mode : %d%d%d", (0x08 & conf)>> 3, (0x04 & conf)>> 2, (0x02 & conf)>> 1 );  //test bit 1 2 3

	printf("Type of Access : %d%d",(0x20 & conf)>> 5, (0x10 & conf)>> 4);  //test bit 3 4

	printf("Null Count : %d", (0x40 & conf)>> 6);  //test bit 6

	printf("Output : %d", (0x80 & conf)>> 7);//test bit 7

	return 0;

}

int timer_test_square(unsigned long freq) {

	return 1;
}

int timer_test_int(unsigned long time) {

	return 1;
}

int timer_test_config(unsigned long timer) {

	unsigned char st;
	int ret;

	ret = timer_get_conf(timer, &st);

	if (ret != 0)
		return 1;

	ret = timer_display_conf(st);

	if ( ret != 0)
		return 1;

	return 0;
}
