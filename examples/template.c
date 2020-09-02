#include "surface.h"
#include "render.h"
#include "image.h"

#define W 1600
#define H 1200

static void sample(surface_t *base, float fps)
{
	surface_clear(base, RGB(0xFFFFFF), 0, 0, base->width, base->height);
}

#include "main.c"