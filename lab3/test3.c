#include <minix/syslib.h>
#include <minix/drivers.h>
#include "keyboard.h"
#include "KBD.h"
#include "i8254.h"
#include "timer.h"

int kbd_test_scan(unsigned short ass) {
	int ipc_status;
	int irq_set=keyboard_subscribe_int();
	message msg;
	int r,scancode=0;

	while( scancode != BREAK_ESC ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					scancode= keyboard_int_handler();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	if(keyboard_unsubscribe_int() != 0)
		return 1;

	return 0;
}

int kbd_test_leds(unsigned short n, unsigned short *leds) {
	int ipc_status;
	int irq_set=timer_subscribe_int();
	message msg;
	int r;
	int counterLed=0;
	int i=0;
	unsigned long cmd;

	while( counterLed/60 <n ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					counterLed++;
					if(counterLed%60==0){
						cmd=keyboard_create_command(leds[i]);

						if (keyboard_notify_controller() != OK)
							return -1;

						if (keyboard_change_led(cmd) == REPEAT)
							continue;

						keyboard_print_ledInfo(leds[i]);
						i++;
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

	if(timer_unsubscribe_int()==1)
		return 1;

	return 0;

}   /*
int kbd_test_leds(unsigned short n, unsigned short *leds) {
	unsigned long cmd;

	int i=0;

	while (i< n)
	{
		cmd=keyboard_create_command(leds[i]);

		if (keyboard_notify_controller() != OK)
			return -1;

		if (keyboard_change_led(cmd) == REPEAT)
			continue;

		keyboard_print_ledInfo(leds[i]);
		sleep(1);
		i++;
	}
}*/
int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
}
