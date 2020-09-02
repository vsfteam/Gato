sinclude scripts/env.mk

X_CFLAGS	+= -std=gnu11 -O3 -g
X_ASFLAGS	+= -O3 -g
X_LIBS		+= m pthread
 #X_LDFLAGS	+= -lprofiler
X_LDFLAGS	+= `pkg-config sdl2 --libs --cflags`
X_INCDIRS	+= include

SRC			+= examples/ui.c examples/examples.c render/*.c image/image.c
NAME		:= Gato