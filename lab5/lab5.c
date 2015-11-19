#include <minix/drivers.h>
#include <float.h>
#include "test5.h"

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
			"\t service run %s -args \"init <unsigned short mode, unsigned short delay>\" \n"
			"\t service run %s -args \"square <unsigned short x,unsigned short y,unsigned short size,unsigned long color>\" \n"
			"\t service run %s -args \"line <unsigned short xi, unsigned short yi,unsigned short xf,unsigned short yf,unsigned long color>\" \n"
			"\t service run %s -args \"xpm <unsigned short xi, unsigned short yi,char *xpm[]>\" \n"
			"\t service run %s -args \"move <unsigned short xi, unsigned short yi,char *xpm[],unsigned short hor,short delta,unsigned short time>\" \n"
			"\t service run %s -args \"controller \n",
			argv[0],argv[0],argv[0],argv[0],argv[0],argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long ch, row, col, attr, width, height;
	char *str;
	long num;

	/* check the function to test: if the first characters match, accept it */
	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if( argc != 4 ) {
			printf("init: wrong number of arguments for test of test_init() \n");
			return 1;
		}
		unsigned short mode=parse_ulong(argv[2],16);
		unsigned short delay=parse_ulong(argv[3],10);

		printf("init:: test_init(%04x,%d)\n",mode,delay);
		test_init(mode,delay);

		return 0;

	} else if(strncmp(argv[1], "square", strlen("square")) == 0) {
		if( argc != 6 ) {
			printf("square: wrong no of arguments for test of test_square() \n");
			return 1;
		}
		unsigned short x=parse_ulong(argv[2],10);
		unsigned short y=parse_ulong(argv[3],10);
		unsigned short size=parse_ulong(argv[4],10);
		unsigned long color =parse_ulong(argv[5],10);

		printf("square :: test_square(%d,%d,%d,%d)\n",x,y,size,color);
		test_square(x,y,size,color);

		return 0;

	}	else if(strncmp(argv[1], "line", strlen("line")) == 0) {
		if( argc != 7 ) {
			printf("line: wrong no of arguments for test of test_line() \n");
			return 1;
		}

		unsigned short xi=parse_ushort(argv[2],10);
		unsigned short yi=parse_ushort(argv[3],10);
		unsigned short xf=parse_ushort(argv[4],10);
		unsigned short yf=parse_ushort(argv[5],10);
		unsigned long color =parse_ulong(argv[6],10);
		printf("line:: test_line(%d,%d,%d,%d,%d)\n",xi,yi,xf,yf,color);
		test_line(xi,yi,xf,yf,color);

		return 0;
	}
	else if(strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
		if( argc != 5 ) {
			printf("xpm: wrong no of arguments for test of test_xpm() \n");
			return 1;
		}
		unsigned short xi=parse_ulong(argv[2],10);
		unsigned short yi=parse_ulong(argv[3],10);
		/*	char *xpm[];//??

		printf("xpm:: kbd_test_xpm(%d,%d,%d)\n",xi, yi,xpm);
		test_xpm(xi, yi,xpm);*/

		return 0;
	}
	else if(strncmp(argv[1], "move", strlen("move")) == 0) {
		if( argc != 8 ) {
			printf("move: wrong no of arguments for test of test_move() \n");
			return 1;
		}
		unsigned short xi=parse_ulong(argv[2],10);
		unsigned short yi=parse_ulong(argv[3],10);
		//	char *xpm[]=parse_ulong(argv[4],10);//??
		unsigned short hor=parse_ulong(argv[5],10);
		short delta=parse_ulong(argv[5],10);
		unsigned short time=parse_ulong(argv[6],10);


		/*	printf("move:: kbd_test_xpm(%d,%d,%d,%d,%d,%d)\n",xi, yi,xpm,hor,delta,time);
		test_move(xi, yi,xpm,hor,delta,time);*/

		return 0;
	}
	else if(strncmp(argv[1], "controller", strlen("controller")) == 0) {
		if( argc != 2 ) {
			printf("controller: wrong no of arguments for test of test_controller() \n");
			return 1;
		}

		printf("controller:: kbd_test_controller()\n");
	//	test_controller();

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
