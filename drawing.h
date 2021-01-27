#ifndef DRAWING_H
#define DRAWING_H

#define OS_DRAW_CENTER

#include "display.h"
#include "oscolor.h"
#include "light.h"

typedef struct 
{
	int a;
	int b;
	int c;
	int s;
	int ymax;
	int ymin;
} ImplicitLine;

class Drawing
{
	public:
		Drawing();
		~Drawing();

		Display* get_display();
		void set_display(Display* display);
		void set_light(Light* light);

		int pixel(int x, int y);
		void draw_pixel(int x, int y, color_t color);
		void draw_texel(
			int x, int y, uint32_t* texture,
			int x0, int y0,
			int x1, int y1,
			int x2, int y2,
			float u0, float v0,
			float u1, float v1,
			float u2, float v2
		);
		void draw_rect(int x, int y, int w, int h, int border_size, color_t color);
		void draw_fill_rect(int x, int y, int w, int h, color_t color);
		void draw_circle(int x, int y, int radius, color_t color);
		void draw_line(int x0, int y0, int x1, int y1, color_t color);
		void draw_line_border(int x0, int y0, int x1, int y1, int border, color_t color);
		void draw_grid(int grid_size, color_t color);

		// Primitive
		void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
		void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
		void fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
		
		//float back_face_culling(int x0, int y0, int x1, int y1, int x2, int y2);
		//float normal_light_direction(int x0, int y0, int x1, int y1, int x2, int y2);

		void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
		void draw_fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
		void draw_textured_triangle(
			int x0, int y0, float u0, float v0,
			int x1, int y1, float u1, float v1,
			int x2, int y2, float u2, float v2,
			uint32_t* texture
		);		
		// Implicit lines
		ImplicitLine implicit_line(int x1, int y1, int x2, int y2);
		int implicit_line_winding_number(ImplicitLine implicit_line, int x, int y);
		void draw_implicit_line(int x1, int y1, int x2, int y2, color_t color);
	private:
		Display* display;
		Light* light;
};

#endif // !DRAWING_H
