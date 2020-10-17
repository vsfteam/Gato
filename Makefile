sinclude scripts/env.mk

MAIN_SRC	:= examples/graph/ui.c
ifeq ("$(origin MAIN)", "command line")
MAIN_SRC	:= $(MAIN)
endif

OPT_FLAGS	+= -O0 -g
X_CFLAGS	+= -std=gnu11 $(OPT_FLAGS)
X_CXXFLAGS	+= -std=c++11 $(OPT_FLAGS)
X_ASFLAGS	+= $(OPT_FLAGS)
X_LIBS		+= m pthread

ifeq ("$(origin PROF)", "command line")
X_DEFINES	+= PROFILE
X_LIBS		+= profiler
endif

ifneq ($(HOSTOS),Darwin)
X_LIBS		+= stdc++ SDL2
else
X_LIBS		+= c++
endif

ifeq ($(HOSTOS),windows)
X_LDFLAGS	+= -lSDL2
else
X_LDFLAGS	+= `pkg-config sdl2 --libs --cflags`
endif

X_INCDIRS	+= include

SRC			+= $(MAIN_SRC) render/*.c image/image.c
NAME		:= Gato