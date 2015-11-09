
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "mouse.h"
#include "KBD.h"

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

	if(sys_outb(STAT_REG, MOUSE_COMMAND)!=OK)
		return 1;
	if(sys_outb(KBD_IN_BUF,DISABLE_STREAM_MODE)!=OK)
		return 1;

	if(mouse_unsubscribe_int() != 0)
		return 1;

	return 0;
}



int test_async(unsigned short idle_time) {
	/* To be completed ... */
}

int test_config(void) {
	/* To be completed ... */
}	

int test_gesture(short length, unsigned short tolerance) {
	/* To be completed ... */
}
