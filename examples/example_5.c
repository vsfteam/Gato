#include "surface.h"
#include "render.h"
#include "image.h"

#define W 300
#define H 300

static void sample(surface_t *base, float fps)
{
	surface_clear(base, RGB(0xFFFFFF), 0, 0, base->width, base->height);
	draw_image(base, "res/appstore.png", 0, 0, W, H);
	//FIXME:
	draw_circle(base, 150, 150, 120, (style_t){
		fill_color : ARGB(0x5FFF0000),
		border_radius : {1, 1, 1, 1},
		stroke_color : ARGB(0xFF00FF00),
		stroke_width : 30,
		n_shadow : 1,
		shadow : (shadow_t[]){0, 0, 20, RGB(0)},
	});
}

#include "main.h"