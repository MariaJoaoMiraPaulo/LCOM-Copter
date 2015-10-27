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

	printf("ass: %d\n",ass);

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
					if(ass==0) {
						scancode=keyboard_c_handler();
					}
					else {
						scancode= keyboard_ass_handler();
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
	if(keyboard_unsubscribe_int() != 0)
		return 1;

	return 0;
}


int kbd_test_leds(unsigned short n, unsigned short *leds) {
	int ipc_status;
	int irq_set=timer_subscribe_int();
	message msg;
	int r;
	int counterLed=0;   //to counter interruptions
	int i=0;
	unsigned long cmd;

	/*if(start_at_zero()==REPEAT)   //put leds at 0 in begin of the program
		start_at_zero();*/

	while( counterLed/60 <n ) { //to do n times
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
	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	unsigned long irq_set_timer = timer_subscribe_int();
	int counter;
	message msg;
	int r,scancode=0,over=1;

	while( over ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */
					counter=n*60;
					scancode=keyboard_c_handler();
					if(scancode==BREAK_ESC)
						over=0;
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
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	if(keyboard_unsubscribe_int() != OK)
		return 1;

	if (timer_unsubscribe_int() != OK)
		return 1;

	return 0;

}
