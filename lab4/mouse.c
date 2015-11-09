#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>
#include "mouse.h"
#include "KBD.h"

int hook_id=MOUSE_IRQ;
unsigned long packet[3];

int mouse_subscribe_int() {
	int tmp = BIT(hook_id);

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE,
			&hook_id)!= OK)  //Subscribes the interruption
		return 1;

	if (sys_irqenable(&hook_id) != OK) //enables the interruption
		return 1;

	return tmp; //returns bit order in interrupt mask if interrupt didn't failed
}

int mouse_unsubscribe_int() {

	if (sys_irqdisable(&hook_id) != OK)
		return 1;

	if (sys_irqrmpolicy(&hook_id) != OK)
		return 1;

	return 0;
}

int mouse_handler() {
	static int counter = 0;
	unsigned long status, byte;
	int someAttemps = 0;

	while (someAttemps < 10) {
		sys_inb(STAT_REG, &status);
		if (status & OBF) {
			if (sys_inb(KBD_OUT_BUF, &byte) != OK) {
				return 1;
			}
			break;
		}
		tickdelay(micros_to_ticks(DELAY_US));
		someAttemps++;
	}

	if (counter == 0) {
		if (byte & FIRST_BYTE) {
			packet[0] = byte;
			counter++;
			return 0;
		}
	} else if (counter == 1) {
		packet[1] = byte;
		counter++;
		return 0;
	} else if (counter == 2) {
		packet[2] = byte;
		mouse_print_packet();
		counter = 0;
		return 1;
	}

	return -1;
}

void mouse_print_packet() {
	printf("One Packet!\n");

	printf("B1 = 0x%02x", packet[0]);
	printf(" B2 = 0x%02x", packet[1]);
	printf(" B3 = 0x%02x", packet[2]);

	if (BIT(0) & packet[0])
		printf(" LB = %d", 1);
	else
		printf(" LB = %d", 0);

	if (BIT(2) & packet[0])
		printf(" MB = %d", 1);
	else
		printf(" MB = %d", 0);

	if (BIT(1) & packet[0])
		printf(" RB = %d", 1);
	else
		printf(" RB = %d", 0);

	if (BIT(6) & packet[0])
		printf(" XOV = %d", 1);
	else
		printf(" XOV = %d", 0);

	if (BIT(7) & packet[0])
		printf(" YOV = %d", 1);
	else
		printf(" YOV = %d", 0);

	if (BIT(4) & packet[0]) {
		unsigned long x_Sign = packet[1];
		x_Sign = ~x_Sign;
		x_Sign += 1;
		x_Sign = -x_Sign;
		printf(" X = %d", x_Sign);
	} else
		printf(" X = %d", packet[1]);

	if (BIT(5) & packet[0]) {
		unsigned long y_Sign = packet[2];
		y_Sign = ~y_Sign;
		y_Sign += 1;
		y_Sign = -y_Sign;
		printf(" Y = %d\n", y_Sign);
	} else
		printf(" Y = %d\n", packet[1]);



}

void configure_environment(){
	unsigned long status;

	sys_inb(STAT_REG, &status);

	if((status & IBF)){ 	//testing if input buffer is full
		sys_outb(STAT_REG,ENABLE_MOUSE);
	}

	tickdelay(micros_to_ticks(DELAY_US));

	sys_outb(STAT_REG, MOUSE_COMMAND);

	tickdelay(micros_to_ticks(DELAY_US));

	sys_inb(STAT_REG, &status);

	if((status & IBF)){ 	//testing if input buffer is full
		sys_outb(KBD_IN_BUF,ENABLE_DATA_PACKETS);
	}

	tickdelay(micros_to_ticks(DELAY_US));
}

int mouse_config_handler(){

	int someAttemps=0;
	static int counter=0;
	unigned long status, byte;

	while (someAttemps < 10) {
		sys_inb(STAT_REG, &status);
		if (status & OBF) {
			if (sys_inb(KBD_OUT_BUF, &byte) != OK) {
				return 1;
			}
			break;
		}
		tickdelay(micros_to_ticks(DELAY_US));
		someAttemps++;
	}

	if (counter==0)
		if(byte & CONFIG_FIRST_BYTE){
			array[0]=byte;
			counter++;
			return 0;
		}
	else if (counter==1){
		array[1]=byte;
		counter++;
		return 0;
	}
	else if (counter==2){
		array[2]=byte;
		mouse_print_config();
		return 1;

	}

	return -1;




}

void mouse_print_config(){


}

