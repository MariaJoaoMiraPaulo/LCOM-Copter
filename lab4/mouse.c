#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include "mouse.h"
#include "KBD.h"

int hook_id;
unsigned long packet[3];

int mouse_subscribe_int()
{
	hook_id=MOUSE_IRQ;
	int tmp=BIT(hook_id);

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)!= OK)  //Subscribes the interruption
		return 1;

	if(sys_irqenable(&hook_id)!=OK) //enables the interruption
		return 1;

	return tmp; //returns bit order in interrupt mask if interrupt didn't failed
}

int mouse_unsubscribe_int()
{
	if( sys_irqrmpolicy(&mouse_hook)!= OK)
		return 1;

	if(sys_irqdisable(&mouse_hook)!=OK)
		return 1;

	return ret;
}

int mouse_handler(){
	static int counter=0;
	unsigned long status, byte;
	int someAttemps=0;

	while( someAttemps<10 ) {
		sys_inb(STAT_REG, &status);
		if( stat & OBF ) {
			if(sys_inb(OUT_BUF, &byte)!=OK){
				return 1;
			}
			break;
		}
		tickdelay(micros_to_ticks(DELAY_US));
		someAttemps++;
	}

	if(counter==0){
		if(byte & FIRST_BYTE){
			packet[0]=byte;
			counter++;
			return 0;
		}
	}
	else if(counter==1){
		packet[1]=byte;
		counter++;
		return 0;
	}
	else if(counter==2){
		packet[2]=byte;
		//mostrar o packet  mouse_print_packet
		counter=0;
		return 0;
	}

	return 1;
}

int mouse_print_packet(){

}






