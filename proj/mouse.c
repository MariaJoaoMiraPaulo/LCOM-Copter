#include "mouse.h"

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>
#include <stdlib.h>
#include "KBD.h"
#include "video_gr.h"
#include "bitmap.h"

int hook_id = MOUSE_IRQ;
unsigned long packet[3];
unsigned long config[3];


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
		//mouse_print_packet();
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
		x_Sign = (0xFF & ~(0xFF & packet[1]));
		//x_Sign = ~x_Sign;
		x_Sign += 1;
		x_Sign = -x_Sign;
		printf("\n X = %d", x_Sign);
	} else
		printf("\n X = %d", packet[1]);

	if (BIT(5) & packet[0]) {
		unsigned long y_Sign = packet[2];
		y_Sign = (0xFF & ~(0xFF & packet[2]));
		//y_Sign = ~y_Sign;
		y_Sign += 1;
		y_Sign = -y_Sign;
		printf(" Y = %d\n", y_Sign);
	} else
		printf(" Y = %d\n", packet[1]);

}

void configure_environment() {
	sys_outb(STAT_REG, MOUSE_COMMAND);
	sys_outb(KBD_IN_BUF, STREAM_MOD);

	tickdelay(micros_to_ticks(DELAY_US));

	sys_outb(STAT_REG, MOUSE_COMMAND);
	sys_outb(KBD_IN_BUF, ENABLE_DATA_PACKETS);

	tickdelay(micros_to_ticks(DELAY_US));
}

int mouse_config_handler() {
	static int counter = 0;
	unsigned long status, byte;

	do {
		sys_inb(STAT_REG, &status);
		tickdelay(micros_to_ticks(DELAY_US));

	} while (!(OBF & status));

	sys_inb(KBD_OUT_BUF, &byte);
	config[0] = byte;

	tickdelay(micros_to_ticks(DELAY_US));

	do {
		sys_inb(STAT_REG, &status);
		tickdelay(micros_to_ticks(DELAY_US));

	} while (!(OBF & status));

	sys_inb(KBD_OUT_BUF, &byte);
	config[1] = byte;

	tickdelay(micros_to_ticks(DELAY_US));

	do {
		sys_inb(STAT_REG, &status);
		tickdelay(micros_to_ticks(DELAY_US));

	} while (!(OBF & status));

	sys_inb(KBD_OUT_BUF, &byte);
	config[2] = byte;

	//mouse_print_config();

	return 0;
}

void mouse_print_config() {
	if (BIT(6) & config[0])
		printf("Remote (polled) mode\n");
	else
		printf("Stream mode\n");

	if (BIT(5) & config[0])
		printf("Data reporting enabled\n");
	else
		printf("Data reporting disabled\n");

	if (BIT(4) & config[0])
		printf("Scaling is 2:1\n");
	else
		printf("scaling is 1:1\n");

	if (BIT(2) & config[0])
		printf("Left button is being pressed\n");
	else
		printf("Left button is not being pressed\n");

	if (BIT(1) & config[0])
		printf("Middle button is being pressed\n");
	else
		printf("Middle button is not being pressed\n");

	if (BIT(0) & config[0])
		printf("Right button is being pressed\n");
	else
		printf("Right button is not being pressed\n");

	switch (config[1] & SET_RESOLUTION) {
	case 0:
		printf("Resolution is set to: 0\n");
		break;
	case 1:
		printf("Resolution is set to: 1\n");
		break;
	case 2:
		printf("Resolution is set to: 2\n");
		break;
	case 3:
		printf("Resolution is set to: 3\n");
		break;
	default:
		printf("Error in resolution\n");
		break;
	}

	printf("Sample Rate is set to : %d\n", config[2]);

}

void while_out_buf_full() {
	unsigned long status, temp;
	do {
		sys_inb(STAT_REG, &status);

		sys_inb(KBD_OUT_BUF, &temp);

	} while (status & OBF);
}

int mouse_is_over(unsigned short tolerance, short length) {

	int delta_x = 0,delta_y = 0;

	if ( packet[0] & RIGHT_BUTTON )
	{
		delta_x += packet[1];
		printf(" \n \ndelta X: %d \n", delta_x);
		delta_y += packet[2];
		printf("delta Y: %d \n \n", delta_y);
	} else {
		delta_x = 0;
		delta_y = 0;
	}

	if (delta_y >= length || abs(delta_y) >= length) {
		if (delta_x <= tolerance || abs(delta_x) <= tolerance)
			return 1;
	}

	return 0;

}

int mouse_left_button_press(){

	if ( packet[0] & LEFT_BUTTON )
	{
		return 1;
	}

	return 0;
}

void atualMousePosition(MouseInfo* mouse){
	unsigned h_res=800;//getHres();
	unsigned v_res=600;//getVres();

	if(BIT(0) & packet[0])
		mouse->lButton=1;
	else
		mouse->lButton=0;

	if(BIT(1) & packet[0])
		mouse->rButton=1;
	else
		mouse->rButton=0;

	if(BIT(2) & packet[0])
		mouse->mButton=1;
	else
		mouse->mButton=0;

	if (BIT(4) & packet[0]) {
		unsigned long x_Sign = packet[1];
		x_Sign = (0xFF & ~(0xFF & packet[1]));
		//x_Sign = ~x_Sign;
		x_Sign += 1;
		x_Sign = -x_Sign;
		mouse->x+=x_Sign;
	} else
		mouse->x+=packet[1];

	if (BIT(5) & packet[0]) {
		unsigned long y_Sign = packet[2];
		y_Sign = (0xFF & ~(0xFF & packet[2]));
		//y_Sign = ~y_Sign;
		y_Sign += 1;
		y_Sign = -y_Sign;
		mouse->y-=y_Sign;
	} else
		mouse->y-=packet[2];

	if(mouse->x<0)
		mouse->x=0;
	if(mouse->x>=h_res-20)
		mouse->x=h_res-20;

	if(mouse->y<0)
		mouse->y=0;
	if(mouse->y>v_res-20)
		mouse->y=v_res-20;

}

void drawMouse(MouseInfo* mouse){

	int i,j;
	for(i=mouse->x;i<mouse->x+2;i++){
		for(j=mouse->y;j<mouse->y+2;j++){
			vg_print_pixel(i,j,rgb(51,255,51));
		}
	}
	printf("PASSEI\n");
//	drawBitmapWithoutBackground(mouse->mouseImage,mouse->x,mouse->y);
	printf("NAO CRASHOU \n");
}
