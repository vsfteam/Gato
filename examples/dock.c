#include "surface.h"
#include "render.h"
#include "image.h"
#include "math.h"

#define W 1200
#define H 300
#define N 10

#define fclampf(v, a, b) fminf(fmaxf(a, v), b)

static surface_t *image[N] = {0};

static char *image_path[N] = {
	"res/appstore.png",
	"res/messages.png",
	"res/calendar.png",
	"res/launchpad.png",
	"res/gamecenter.png",
	"res/systempreferences.png",
	"res/textedit.png",
	"res/facetime.png",
	"res/dictionnary.png",
	"res/safari.png",
};
static void motion_get_xy(int *x, int *y);

static surface_t *image_get(int index)
{
	if (image[index] == 0)
	{
		image[index] = surface_image_load(image_path[index], 100, 100);
	}
	return image[index];
}

static void draw_icon(surface_t *base, float size, float x, float y, surface_t *image)
{
	surface_t *s = surface_image_resize(image, size, size);
	surface_blit(base, s, x, y);
	surface_free(s);
}

static float calc(int dis)
{
	return fclampf(fabsf(60 * 1.8 - 0.25 * fabsf(dis)), 60, 60 * 1.8);
}

static float f(float x, float b, float A)
{
	float f1 = x;
	float f2 = 0;
	float k = 130;

	if ((x > b - k) && (x < b + k))
	{
		f2 = A * sinf(3.1415926f * (x - b) / (2 * k)) + A;
	}
	else if (x >= b + k)
	{
		f2 = 2 * A;
	}

	return f1 + f2;
}

static void sample(surface_t *base, float fps)
{
	printf("fps:%f\n", fps);
	surface_clear(base, RGB(0xFFFFFF), 0, 0, base->width, base->height);
	int m_x, m_y;
	float size[N] = {0};
	float w[N] = {0};
	float off[N] = {0};

	int total = 0;

	for (int i = 0; i < N; i++)
	{
		w[i] = 60;
		size[i] = 60;
	}

	motion_get_xy(&m_x, &m_y);

	float left = W / 2 - 60 * N / 2.0;
	float right = W / 2 + 60 * N / 2.0;
	static float A = 0;

	if (m_x < left || m_x > right)
	{
		A = fclampf(A - 7, 0, 60);
	}
	else
	{
		A = fclampf(A + 7, 0, 60);
	}

	float center = f(m_x, m_x, A);
	for (int i = 0, x = W / 2 - 60 * N / 2.0; i < N; i++)
	{
		float d1 = f(x, m_x, A) - center;
		off[i] = d1;
		x += w[i];
		float d2 = f(x, m_x, A) - center;
		size[i] = d2 - d1;
	}

	draw_rectage(base, m_x + off[0], H - 60, size[N - 1] + off[N - 1] - off[0], 60, 10, (style_t){
		fill_color : RGB(0xE1E1E1),
		border_radius : {1, 1, 0, 0},
		stroke_color : RGB(0xB2B2B2),
		stroke_width : 1,
	});
	for (int i = 0; i < N; i++)
	{
		draw_icon(base, size[i], m_x + off[i], H - size[i], image_get(i));
	}
}

#include "main.c"