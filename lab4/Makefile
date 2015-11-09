# Makefile for the lab4 driver (based on that of hello).

COMPILER_TYPE= gnu

CC=gcc

PROG=	lab4
SRCS=	mouse.c test4.c lab4.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+=	 -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
