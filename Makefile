sinclude scripts/env.mk

MAIN_SRC	:= examples/graph/ui.c
ifeq ("$(origin MAIN)", "command line")
MAIN_SRC	:= $(MAIN)
endif

OPT_FLAGS	+= -O0 -g
X_CFLAGS	+= -std=gnu11 $(OPT_FLAGS)
X_ASFLAGS	+= $(OPT_FLAGS)
X_LIBS		+= m pthread c++
X_CXXFLAGS	+= -std=c++11 $(OPT_FLAGS)
# X_DEFINES	+= PROFILE
# X_LDFLAGS	+= -lprofiler
X_LDFLAGS	+= `pkg-config sdl2 --libs --cflags`
X_INCDIRS	+= include

SRC			+= $(MAIN_SRC) render/*.c image/image.c
NAME		:= Gato