sinclude scripts/env.mk

X_CFLAGS	+= -std=gnu11 -O3 -g
X_ASFLAGS	+= -O3 -g
X_LIBS		+= m pthread
X_LDFLAGS	+= `pkg-config sdl2 --libs --cflags` -lprofiler
X_INCDIRS	+= include

SRC			+= examples/example_3.c examples/examples.c render/*.c image/image.c
NAME		:= Gato