#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>
#include "KBD.h"
#include "keyboard.h"
#include <stdbool.h>

int hook_id;
char command;
int OnOrOff;  //this variable is used in function print leds, is too know if led was turn on or off
unsigned int Caps=0,Scroll=0,Num=0;

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
	if(sys_irqdisable(&hook_id)!=0) //enables the interruption
			return 1;

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


int keyboard_c_handler()
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
				if(!is2byte)                 //test if is a 2 byte or 1 byte scancode
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

unsigned long keyboard_create_command(int ledToChange)
{
	unsigned long cmd;

	switch(ledToChange)   //0=scrool, 1=num , 2=caps
	{
	case 0:
		if (Scroll==0)
		{
			Scroll=SCROLL_ON;
			OnOrOff=1;
		}
		else
		{
			Scroll=0;
			OnOrOff=0;
		}
		break;
	case 1:
		if (Num==0)
		{
			Num=NUM_ON;
			OnOrOff=1;
		}
		else
		{
			Num=0;
			OnOrOff=0;
		}
		break;
	case 2:
		if (Caps==0)
		{
			Caps=CAPS_ON;
			OnOrOff=1;
		}

		else
		{
			Caps=0;
			OnOrOff=0;
		}
		break;

	}

	cmd=Caps+Num+Scroll;
	return cmd;

}

int keyboard_notify_controller()
{
	unsigned long msg;

	do{

		if (sys_outb( KBD_IN_BUF, SET_LED) != OK)  //sends command 0xED
			return -1;

		tickdelay(micros_to_ticks(DELAY_US));  //waits for keyboard controller

		if (sys_inb( KBD_OUT_BUF, &msg)!=OK)   //checks if  all went well
			return -1;

	}
	while (msg != ACK);

	return 0;

}

int keyboard_change_led(unsigned long cmd)
{
	unsigned long msg;

	do {
		if (sys_outb( KBD_IN_BUF, cmd)!=OK)  //sends command to modify led
			return -1;

		tickdelay(micros_to_ticks(DELAY_US));    //waits for keyboard controller

		if (sys_inb( KBD_OUT_BUF,&msg)==REPEAT)  //checks if  all went well
			return -1;

	}
	while (msg==RESEND);    //trys to deal with possible errors

	if (msg==ERROR)
		return 1;

	return 0;

}

void keyboard_print_ledInfo(int ledToPrint)
{
	switch (ledToPrint)
	{
	case 0:
		if(OnOrOff==0)    //checks if leds was turn on or off
		{
			printf("Scroll Lock Off \n");
		}
		else printf("Scroll lock On \n");
		break;
	case 1:
		if(OnOrOff==0)     //checks if leds was turn on or off
		{
			printf("Num Lock Off \n");
		}
		else printf("Num lock On \n");
		break;
	case 2:
		if(OnOrOff==0)     //checks if leds was turn on or off
		{
			printf("Caps Lock Off \n");
		}
		else printf("Caps lock On \n");
		break;

	}
}

/*int start_at_zero()
{
	if (keyboard_notify_controller() != OK)
		return 1;

	tickdelay(micros_to_ticks(DELAY_US));

	if (keyboard_change_led(0) != OK)
		return 1;
}
 */

/*int keyboard_ass_handler()
{
	unsigned long res;
	int ret,output_buffer;
	char status;
	_Bool is2byte=false;

	while(1)
	{
		sys_enable_iop(SELF);
		res=assemblyHandler();     //res is the eax returned by asm_handler

		output_buffer=res;
		if(output_buffer != TWO_BYTE)       //see if the scancode is two byte length
		{
			if(!is2byte)                 //test if is a 2 byte or 1 byte scancode
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



}
*/
