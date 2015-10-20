#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>
#include "KBD.h"
#include "keyboard.h"
#include <stdbool.h>

int hook_id;
char command;

int keyboard_subscribe_int(void )
{
	hook_id=1;
	int tmp=BIT(hook_id);

	if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE,&hook_id)!= 0)  //Subscribes the interruption
		return 1;

	if(sys_irqenable(&hook_id)!=0) //enables the interruption
		return 1;

	return tmp; //returns bit order in interrupt mask if interrupt didn't failed
}

void keyboard_print(int scancode)
{
	if ((char)scancode & MSB)
		printf("BREAKCODE : %X",scancode);
	else
		printf("MAKECODE : %X",scancode)
}


int keyboard_handler_scan()
{
	unsigned long res;
	int ret;
	char status, output_buffer;
	_Bool wait=false;

	while(tickdelay(micros_to_ticks(DELAY_US)))
	{
		ret=sys_inb(STAT_REG, &res);
		if(ret != 0)
			return 1;

		status =(char)res;
		command=0x01;
		if((status & command) && !(status & (TIMEOUT | PARITY)) )
		{
			ret=sys_inb(KBD_OUT_BUF, &res);
			if(ret != 0)
				return 1;
			output_buffer=(char)res;
			if(output_buffer != WAIT)
			{
				if(!wait)
					return (int)output_buffer;
				else
					return ((WAIT << 8)| output_buffer);
			}
				wait=true;
			}
		}
	}






