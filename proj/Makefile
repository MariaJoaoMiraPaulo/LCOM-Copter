# Makefile for the proj driver (based on that of hello).
  
COMPILER_TYPE= gnu

CC=gcc

PROG=	proj
SRCS=	vbe.c video_gr.c timer.c keyboard.c copter.c main.c 
SRCS+=	GameState.c Margins.c mouse.c bitmap.c Singleplayer.c Menu.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+=	 -ldriver -lsys -llm

LDFLAGS+= -L .

MAN=
  
.include <bsd.prog.mk>
.include <bsd.gcc.mk>
