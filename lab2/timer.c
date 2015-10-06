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
		command=command |TIMER_RB_SEL(0);
		break;
	case 1:
		command=command |TIMER_RB_SEL(1);
	case 1:
		command=command |TIMER_RB_SEL(2);
	}

	ret=  sys_outb(TIMER_CTRL,command);
	unsigned long res;

	if (ret !=0 ) //error
		return 1;

	switch (timer)
		{
		case 0:
			ret= sys_inb(TIMER_0,res);
			break;
		case 1:
			ret= sys_inb(TIMER_1,res);
		case 1:
			ret= sys_inb(TIMER_2,res);
		}


	if(ret!=0)
		return 1;

	*st=res;


	return 0;
}

int timer_display_conf(unsigned char conf) {
	

}

int timer_test_square(unsigned long freq) {
	
	return 1;
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer) {
	
	return 1;
}
