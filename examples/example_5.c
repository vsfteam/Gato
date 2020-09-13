#include "surface.h"
#include "render.h"
#include "image.h"

#define W 300
#define H 300

static void sample(surface_t *base, float fps)
{
	surface_clear(base, RGB(0xFFFFFF), 0, 0, base->width, base->height);
	draw_image(base, "res/appstore.png", 0, 0, W, H);
	draw_circle(base, 150, 150, 120, (style_t){
		fill_color : ARGB(0x2FFFFFFF),
		border_radius : {1, 1, 1, 1},
		stroke_color : ARGB(0x2FB2B2B2),
		stroke_width : 2,
	});
}

#include "main.h"