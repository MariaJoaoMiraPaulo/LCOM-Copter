#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "mouse.h"
#include "KBD.h"
#include "timer.h"
#include "keyboard.h"

int test_packet(unsigned short cnt){
	int ipc_status;
	int irq_set=mouse_subscribe_int();
	int r;
	message msg;

	configure_environment();

	while( cnt>0 ) {
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("Driver_receive failed\n");
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					if(mouse_handler() == 1)
						cnt--;
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {
			printf("No interruptions");
		}
	}

	/*if(sys_outb(STAT_REG, MOUSE_COMMAND)!=OK)
		return 1;

	if(sys_outb(KBD_IN_BUF,DISABLE_STREAM_MODE)!=OK)
		return 1;*/
	while_out_buf_full();

	if(mouse_unsubscribe_int() != 0)
		return 1;

	return 0;
}

int test_async(unsigned short idle_time) {
	int ipc_status;
	unsigned long irq_set_mouse =  mouse_subscribe_int();
	unsigned long irq_set_timer = timer_subscribe_int();
	int counter=idle_time*60;
	message msg;
	int r,over=1;

	configure_environment();

	while( over ) {
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_mouse) { /* subscribed interrupt */
					counter=idle_time*60;
					mouse_handler();
				}
				else if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */
					counter--;
					if(counter==0)
					{
						over=0;
						printf("Function is over!\n");
					}
				}
				break;

			default:
				break;
			}
		} else {
		}
	}

	/*if(sys_outb(STAT_REG, MOUSE_COMMAND)!=OK)
		return 1;

	if(sys_outb(KBD_IN_BUF,DISABLE_STREAM_MODE)!=OK)
		return 1;*/

	if(mouse_unsubscribe_int() != 0)
		return 1;

	if (timer_unsubscribe_int() != OK)
		return 1;

	while_out_buf_full();

	return 0;
}

int test_config(void) {
	int ipc_status;
	int irq_set=mouse_subscribe_int();
	int r,over=1;
	unsigned long status;
	message msg;

	do{
		sys_outb(STAT_REG,MOUSE_COMMAND);
		sys_outb(KBD_IN_BUF, DISABLE_STREAM_MODE);
		do{
			sys_inb(STAT_REG,&status);
			tickdelay(micros_to_ticks(DELAY_US));

		}while(!(OBF & status));
		sys_inb(KBD_OUT_BUF,&status);
	}while(status!=ACK);

	do{
		sys_outb(STAT_REG,MOUSE_COMMAND);
		sys_outb(KBD_IN_BUF,STATUS_REQUEST);
		do{
			sys_inb(STAT_REG,&status);
			tickdelay(micros_to_ticks(DELAY_US));

		}while(!(OBF & status));
		sys_inb(KBD_OUT_BUF,&status);
	}while(status!=ACK);

	mouse_config_handler();

	while_out_buf_full();
	if(mouse_unsubscribe_int() != 0)
		return 1;

	return 0;

}	

int test_gesture(short length, unsigned short tolerance) {
	int ipc_status;
	int irq_set=mouse_subscribe_int();
	int r,over=1;
	unsigned long status;
	message msg;

	configure_environment();

	do{
		sys_outb(STAT_REG,MOUSE_COMMAND);
		sys_outb(KBD_IN_BUF, ENABLE_MOUSE);
		sys_inb(KBD_OUT_BUF,&status);
	}while(status!=ACK);

	while( over ) {
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			printf("Driver_receive failed\n");
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					if(mouse_handler()==1){

						if (mouse_is_over(tolerance,length)==1){
							over=0;
						}
					}
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {
			printf("No interruptions");
		}
	}

	/*if(sys_outb(STAT_REG, MOUSE_COMMAND)!=OK)
			return 1;

		if(sys_outb(KBD_IN_BUF,DISABLE_STREAM_MODE)!=OK)
			return 1;*/
	if(mouse_unsubscribe_int() != 0)
		return 1;

	while_out_buf_full();

	return 0;
}

int test_proj(){
	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	unsigned long irq_set_mouse =  mouse_subscribe_int();
	message msg;
	int r,over=1,scancode=0;
	printf("INICIO");

	configure_environment();

	while( over ) {
		/* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)){
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */
					scancode=keyboard_space_proj();
					if(scancode==BREAK_ESC){
						over=0;
					}

				}
				if(msg.NOTIFY_ARG & irq_set_mouse){
					if(mouse_handler()==1)
					{
						if (mouse_over_proj()==1)
						{
							printf("SOBE");

						}
						else (printf("DESCE"));

					}
				}

				break;

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}


	/*if(sys_outb(STAT_REG, MOUSE_COMMAND)!=OK)
			return 1;

		if(sys_outb(KBD_IN_BUF,DISABLE_STREAM_MODE)!=OK)
			return 1;*/

	if(mouse_unsubscribe_int() != 0)
		return 1;

	if (timer_unsubscribe_int() != OK)
		return 1;

	while_out_buf_full();

	return 0;
}
