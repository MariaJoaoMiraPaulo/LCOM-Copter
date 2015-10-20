#include <minix/drivers.h>

#include "test3.h"
#include "keyboard.h"
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
			"\t service run %s -args \"scan <asm>\" \n"
			"\t service run %s -args \"leds <n> <toggle>\" \n",
			argv[0],argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long ch, row, col, attr, width, height;
	char *str;
	long num;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
		if( argc != 3 ) {
			printf("scan: wrong no of arguments for test of kbd_test_scan() \n");
			return 1;
		}
		unsigned short assembly;
		assembly = parse_ulong(argv[2], 10);
		printf("scan:: kbd_test_scan(%d)\n", assembly);
		kbd_test_scan(assembly);
		return 0;
	} else if(strncmp(argv[1], "leds", strlen("leds")) == 0) {
		if(argc != 3){
			printf("leds: wrong no of arguments for test of kbd_test_leds() \n");
			return 1;
		}
		unsigned short n;
		unsigned short *toggle;
		n = parse_ulong(argv[2], 10);
		//toggle = parse_ulong(argv[3], 10);
		printf("leds:: kbd_test_leds(%d ,%d )\n", n, toggle );
		kbd_test_leds(n, toggle);
		return 0;
	}
	else {
		printf("video_txt: non valid function \"%s\" to test\n", argv[1]);
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
		printf("video_txt: parse_ulong: no digits were found in %s \n", str);
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
		printf("video_txt: parse_long: no digits were found in %s \n", str);
		return LONG_MAX;
	}

	/* Successful conversion */
	return val;
}
