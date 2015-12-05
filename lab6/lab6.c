#include <minix/drivers.h>
#include <float.h>
#include "test6.h"



static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);
static unsigned short parse_ushort(char *str, int base);
static short parse_short(char *str, int base);

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
			"\t service run %s -args \"conf \" \n"
			"\t service run %s -args \"date \" \n"
			"\t service run %s -args \"int \" \n"
			,argv[0],argv[0],argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long ch, row, col, attr, width, height;
	char *str;
	long num;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "conf", strlen("conf")) == 0) {
		if( argc != 2 ) {
			printf("conf: wrong number of arguments for test of test_init() \n");
			return 1;
		}

		printf("conf:: test_conf()\n");
		rtc_test_conf();

		return 0;

	} else if(strncmp(argv[1], "date", strlen("date")) == 0) {
		if( argc != 2 ) {
			printf("date: wrong no of arguments for test of rtc_test_date() \n");
			return 1;
		}

		printf("date :: rtc_test_date()\n");
		rtc_test_date();

		return 0;

	}	else if(strncmp(argv[1], "int", strlen("int")) == 0) {
		if( argc != 2 ) {
			printf("int: wrong no of arguments for test of rtc_test_int() \n");
			return 1;
		}

		printf("line:: rtc_test_int()\n");
		rtc_test_int();

		return 0;
	}



	else {
		printf("Rtc: non valid function \"%s\" to test\n", argv[1]);
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

static unsigned short parse_ushort(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtoul(str, &endptr, base);

	if ((errno == ERANGE && val == USHRT_MAX )
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return USHRT_MAX;
	}

	if (endptr == str) {
		printf("vge_txt: parse_ushort: no digits were found in %s \n", str);
		return USHRT_MAX;
	}

	/* Successful conversion */
	return val;
}

static short parse_short(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtol(str, &endptr, base);

	if ((errno == ERANGE && (val == SHRT_MAX || val == SHRT_MIN))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return SHRT_MAX;
	}

	if (endptr == str) {
		printf("vbe_txt: parse_short: no digits were found in %s \n", str);
		return SHRT_MAX;
	}

	/* Successful conversion */
	return val;
}
