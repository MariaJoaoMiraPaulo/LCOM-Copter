# Makefile for the lab6 driver (based on that of hello).
  
COMPILER_TYPE= gnu

CC=gcc

PROG=	lab6
SRCS=	test6.c lab6.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+=	 -ldriver -lsys -lvt

LDFLAGS+= -L .

MAN=
  
.include <bsd.prog.mk>
.include <bsd.gcc.mk>
