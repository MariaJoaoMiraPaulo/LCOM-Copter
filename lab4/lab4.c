#include <minix/drivers.h>

#include "test4.h"
#include "mouse.h"
#include "KBD.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

	/* Initialize service */

	sef_startup();

	if ( argc == 1 ) {
		print_usage(argv);
		return 0;
	} else {
		proc_args(argc, argv);
	}


	return 0;

}

static void print_usage(char *argv[]) {
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"packet <int cnt>\" \n"
			"\t service run %s -args \"async <int idle_time>\" \n"
			"\t service run %s -args \"config\" \n"
			"\t service run %s -args \"gesture <short length, unsigned short tolerance>\" \n"
			"\t service run %s -args \"proj\" \n",
			argv[0],argv[0],argv[0],argv[0],argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long ch, row, col, attr, width, height;
	char *str;
	long num;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "packet", strlen("packet")) == 0) {
		if( argc != 3 ) {
			printf("packet: wrong no of arguments for test of test_packet() \n");
			return 1;
		}
		unsigned short cnt=parse_ulong(argv[2],10);

		printf("packet:: test_packet(%d)\n",cnt);
		test_packet(cnt);

		return 0;

	} else if(strncmp(argv[1], "async", strlen("async")) == 0) {
		if( argc != 3 ) {
			printf("async: wrong no of arguments for test of test_async() \n");
			return 1;
		}
		unsigned short idle_time=parse_ulong(argv[2],10);

		printf("async :: test_async(%d)\n",idle_time);
		test_async(idle_time);

		return 0;

	}	else if(strncmp(argv[1], "config", strlen("config")) == 0) {
		if( argc != 2 ) {
			printf("config: wrong no of arguments for test of test_config() \n");
			return 1;
		}
		printf("config:: test_config()\n");
		test_config();

		return 0;
	}
	else if(strncmp(argv[1], "gesture", strlen("gesture")) == 0) {
		if( argc != 4 ) {
			printf("gesture: wrong no of arguments for test of test_gesture() \n");
			return 1;
		}
		short length=parse_ulong(argv[2],10);
		unsigned short tolerance=parse_ulong(argv[3],10);

		printf("gesture:: kbd_test_gesture(%d,%d)\n",length, tolerance);
		test_gesture(length,tolerance);

		return 0;
	}
	else if(strncmp(argv[1], "proj", strlen("proj")) == 0) {
			if( argc != 2 ) {
				printf("proj: wrong no of arguments for test of test_gesture() \n");
				return 1;
			}

			test_proj();

			return 0;
		}

	else {
		printf("Mouse: non valid function \"%s\" to test\n", argv[1]);
		return 1;
	}
}

static unsigned long parse_ulong(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtoul(str, &endptr, base);

	if ((errno == ERANGE && val == ULONG_MAX )
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("Mouse_txt: parse_ulong: no digits were found in %s \n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}

static long parse_long(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtol(str, &endptr, base);

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return LONG_MAX;
	}

	if (endptr == str) {
		printf("Mouse_txt: parse_long: no digits were found in %s \n", str);
		return LONG_MAX;
	}

	/* Successful conversion */
	return val;
}
