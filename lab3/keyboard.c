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

int keyboard_unsubscribe_int()
{
	int ret = sys_irqrmpolicy(&hook_id);

	if (ret < 0)
		return -1;

	return ret;
}

void keyboard_print(int scancode)
{
	if ((char)scancode & MSB)
		printf("BREAKCODE : %02X\n",scancode);
	else
		printf("MAKECODE : %02X\n",scancode);
}


int keyboard_int_handler()
{
	unsigned long res;
	int ret,output_buffer;
	char status;
	_Bool is2byte=false;

	while(1)
	{
		if(sys_inb(STAT_REG, &res) != OK ) //read keyboard controller
			return 1;

		status =(char)res;

		if((status & STATUS_READY_OUT) && !(status & (TIMEOUT | PARITY)) )  //see if its all ok
		{
			if(sys_inb(KBD_OUT_BUF, &res) != OK)     //see if occurred some type of error
				return 1;

			output_buffer=res;
			if(output_buffer != TWO_BYTE)       //see if the scancode is two byte length
			{
				if(!is2byte)                 //see what type of print is the most suitable
				{
					keyboard_print(output_buffer);
					return output_buffer;
				}
				else
				{
					keyboard_print(((TWO_BYTE << 8)| output_buffer));  //shift 0xE0 for the left byte
					return ((TWO_BYTE << 8)| output_buffer);
				}
			}
			else
			{
				is2byte=true;   //the scancode is two byte length
			}
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

}






