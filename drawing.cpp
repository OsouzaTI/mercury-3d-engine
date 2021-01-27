#include <iostream>
#include "drawing.h"
#include "osmath.h"
#include "triangle.h"

#include "texture.h"

Drawing::Drawing() {
	this->display = NULL;
}
Drawing::~Drawing() {}

Display* Drawing::get_display()
{
    return this->display;
}

int Drawing::pixel(int x, int y)
{
	return ((this->display->view_port.width * y) + x);
}

void Drawing::set_display(Display* display)
{
	this->display = display;
}

void Drawing::set_light(Light* light)
{
    this->light = light;
}

void Drawing::draw_pixel(int x, int y, color_t color)
{
    if (x >= 0 && x < this->display->view_port.width && y >= 0 && y < this->display->view_port.height) {
        color_t* color_buffer = this->display->get_color_buffer();
        color_buffer[pixel(x, y)] = color;
    }
}

void Drawing::draw_texel(int x, int y, uint32_t* texture, int x0, int y0, int x1, int y1, int x2, int y2, float u0, float v0, float u1, float v1, float u2, float v2)
{
    vect3<float> weights = TriangleHelper::barycentric_weights(x, y, x0, y0, x1, y1, x2, y2);
    float alpha = weights.x;
    float beta  = weights.y;
    float gamma = weights.z;

    float interpolated_u = u0 * alpha + u1 * beta + u2 * gamma;
    float interpolated_v = v0 * alpha + v1 * beta + v2 * gamma;

    unsigned int texture_x = abs(static_cast<int>(interpolated_u * texture_width));
    unsigned int texture_y = abs(static_cast<int>(interpolated_v * texture_height));
    
    draw_pixel(x, y, texture[(texture_width * texture_y) + texture_x]);

}

void Drawing::draw_rect(int x, int y, int w, int h, int border_size, color_t color) {

    for (int yy = 0; yy < h; yy++)
    {
        for (int xx = 0; xx < w; xx++)
        {
            int _xx = x + xx;
            int _yy = y + yy;
            if (xx == 0 || xx <= 0 + border_size)
                draw_pixel(_xx, _yy, color);
            if (yy == 0 || yy <= 0 + border_size)
                draw_pixel(_xx, _yy, color);
            if (yy == h - 1 || yy >= h - border_size)
                draw_pixel(_xx, _yy, color);
            if (xx == w - 1 || xx >= w - border_size)
                draw_pixel(_xx, _yy, color);

        }
    }

}

void Drawing::draw_fill_rect(int x, int y, int w, int h, color_t color) {

    for (int yy = 0; yy < h; yy++)
    {
        for (int xx = 0; xx < w; xx++)
        {
            int _xx = x + xx;
            int _yy = y + yy;
            draw_pixel(_xx, _yy, color);
        }
    }

}

void Drawing::draw_circle(int x, int y, int radius, color_t color) {

    int xx = 0;
    int yy = radius;
    int dd = 3 - (2 * radius);

    draw_pixel(x + xx, y + yy, color);
    draw_pixel(x - xx, y + yy, color);
    draw_pixel(x + xx, y - yy, color);
    draw_pixel(x - xx, y - yy, color);

    draw_pixel(x + yy, y + xx, color);
    draw_pixel(x - yy, y + xx, color);
    draw_pixel(x + yy, y - xx, color);
    draw_pixel(x - yy, y - xx, color);

    while (yy >= xx)
    {
        xx++;
        if (dd > 0)
        {
            yy--;
            dd = dd + 4 * (xx - yy) + 10;
        }
        else {
            dd = dd + 4 * xx + 6;
        }

        draw_pixel(x + xx, y + yy, color);
        draw_pixel(x - xx, y + yy, color);
        draw_pixel(x + xx, y - yy, color);
        draw_pixel(x - xx, y - yy, color);
        draw_pixel(x + yy, y + xx, color);
        draw_pixel(x - yy, y + xx, color);
        draw_pixel(x + yy, y - xx, color);
        draw_pixel(x - yy, y - xx, color);
    }


}

// Draw line algorithm DDA
// comments in draw line are portuguese
void Drawing::draw_line(int x0, int y0, int x1, int y1, color_t color) {
    // calcula os deltas respectivos
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);
    // variavel destinada ao maior delta
    int side_lenght = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);
    // taxa de incremento dos eixos
    float x_inc = delta_x / (float)side_lenght;
    float y_inc = delta_y / (float)side_lenght;

    // valor atual do incrementos
    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= side_lenght; i++)
    {
        draw_pixel((int)round(current_x), (int)round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }

}

void Drawing::draw_line_border(int x0, int y0, int x1, int y1, int border_size, color_t color) {
    // para saber o que o algoritmo esta fazendo
    // verifique a fun��o draw_line

    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);

    int side_lenght = 1;
    if (abs(delta_x) >= abs(delta_y)) {
        side_lenght = abs(delta_x);
    }
    else {
        side_lenght = abs(delta_y);
    }

    float x_inc = delta_x / (float)side_lenght;
    float y_inc = delta_y / (float)side_lenght;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i < side_lenght; i++)
    {
        draw_fill_rect(
            (int)current_x,
            (int)current_y,
            border_size,
            border_size,
            color
        );
        current_x += x_inc;
        current_y += y_inc;
    }


}

void Drawing::draw_grid(int grid_size, color_t color) {
    for (int i = 0; i < this->display->width; i += grid_size)
    {
        for (int j = 0; j < this->display->height; j += grid_size)
        {
            draw_pixel(i, j, color);
        }
    }
}

void Drawing::fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
    float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

    float x_start = x0;
    float x_end = x0;

    for (int y = y0; y <= y2; y++)
    {
        draw_line((int)x_start, y, (int)x_end, y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}

void Drawing::fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
    float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

    float x_start = x2;
    float x_end = x2;

    for (int y = y2; y >= y0; y--)
    {
        draw_line((int)x_start, y, (int)x_end, y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

void Drawing::fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    float dot_prod = TriangleHelper::back_face_culling(x0, y0, x1, y1, x2, y2);

    if (y0 > y1) {
        Math::swap(&y0, &y1);
        Math::swap(&x0, &x1);
    }
    if (y1 > y2) {
        Math::swap(&y1, &y2);
        Math::swap(&x1, &x2);
    }
    if (y0 > y1) {
        Math::swap(&y0, &y1);
        Math::swap(&x0, &x1);
    }


    if (y1 == y2) {
        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else if (y0 == y1) {
        // Draw flat-top triangle
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else {

        //vec2_t mid = GeoMath::triangle_mid_point(t);
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;
        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);
        // Draw flat-top triangle
        fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);

    }

}

void Drawing::draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

void Drawing::draw_fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    if (y0 > y1) {
        Math::swap(&y0, &y1);
        Math::swap(&x0, &x1);
    }
    if (y1 > y2) {
        Math::swap(&y1, &y2);
        Math::swap(&x1, &x2);
    }
    if (y0 > y1) {
        Math::swap(&y0, &y1);
        Math::swap(&x0, &x1);
    }


    if (y1 == y2) {
        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else if (y0 == y1) {
        // Draw flat-top triangle
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    }
    else {

        //vec2_t mid = GeoMath::triangle_mid_point(t);
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;
        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);
        // Draw flat-top triangle
        fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);

    }
}

void Drawing::draw_textured_triangle(int x0, int y0, float u0, float v0, int x1, int y1, float u1, float v1, int x2, int y2, float u2, float v2, uint32_t* texture)
{
    // we need to sort the vertices by y-coodinates ascending (y0 < y1 < y2)
    if (y0 > y1) {
        Math::swap<int>(&y0, &y1);
        Math::swap<int>(&x0, &x1);
        Math::swap<float>(&u0, &u1);
        Math::swap<float>(&v0, &v1);
    }
    if (y1 > y2) {
        Math::swap<int>(&y1, &y2);
        Math::swap<int>(&x1, &x2);
        Math::swap<float>(&u1, &u2);
        Math::swap<float>(&v1, &v2);
    }
    if (y0 > y1) {
        Math::swap<int>(&y0, &y1);
        Math::swap<int>(&x0, &x1);
        Math::swap<float>(&u0, &u1);
        Math::swap<float>(&v0, &v1);
    }
    // render the upper part of the triangle (flat-bottom)
    float inv_slop_1 = 0;
    float inv_slop_2 = 0;
    if (y1 - y0 != 0) inv_slop_1 = (float)(x1 - x0) / abs(y1 - y0);
    if (y2 - y0 != 0) inv_slop_2 = (float)(x2 - x0) / abs(y2 - y0);

    if (y1 - y0 != 0) {
        for (int y = y0; y <= y1; y++)
        {
            int start_x = static_cast<int>(x1 + (y - y1) * inv_slop_1);
            int end_x = static_cast<int>(x0 + (y - y0) * inv_slop_2);

            if (end_x < start_x) Math::swap<int>(&start_x, &end_x);

            for (int x = start_x; x < end_x; x++)
            {
                draw_texel(
                    x, y, texture,
                    x0, y0, // point_a
                    x1, y1, // point_b
                    x2, y2, // point_c
                    u0, v0,
                    u1, v1,
                    u2, v2
                );
            }
        }
    }

    // render the bottom part of the triangle (flat-top)
    inv_slop_1 = 0;
    inv_slop_2 = 0;
    if (y2 - y1 != 0) inv_slop_1 = (float)(x2 - x1) / abs(y2 - y1);
    if (y2 - y0 != 0) inv_slop_2 = (float)(x2 - x0) / abs(y2 - y0);

    if (y2 - y1 != 0) {
        for (int y = y1; y <= y2; y++)
        {
            int start_x = static_cast<int>(x1 + (y - y1) * inv_slop_1);
            int end_x = static_cast<int>(x0 + (y - y0) * inv_slop_2);

            if (end_x < start_x) Math::swap<int>(&start_x, &end_x);

            for (int x = start_x; x < end_x; x++)
            {
                draw_texel(
                    x, y, texture,
                    x0, y0, // point_a
                    x1, y1, // point_b
                    x2, y2, // point_c
                    u0, v0,
                    u1, v1,
                    u2, v2
                );
            }
        }
    }

}

ImplicitLine Drawing::implicit_line(int x1, int y1, int x2, int y2)
{
    int a = y2 - y1;
    int b = x1 - x2;
    int c = -(a * x1 + b * y1);
    int s = Math::sign<int>(a);
    ImplicitLine _implicit_line{
        a * s,
        b * s,
        c * s,
        s,
        Math::max<int>(y1, y2),
        Math::min<int>(y1, y2)
    };

    return _implicit_line;
}

int Drawing::implicit_line_winding_number(ImplicitLine implicit_line, int x, int y)
{
    bool condicion = y > implicit_line.ymin && y <= implicit_line.ymax &&
        implicit_line.a * x + implicit_line.b * y + implicit_line.c < 0;

    if (condicion)return implicit_line.s;
    return 0;
}

void Drawing::draw_implicit_line(int x1, int y1, int x2, int y2, color_t color)
{
    ImplicitLine _implicit_line = implicit_line(x1, y1, x2, y2);
    for (int x = 0; x < this->display->width; x++)
    {
        for (int y = 0; y < this->display->height; y++)
        {
            int sum_implicit_line = implicit_line_winding_number(_implicit_line, x, y);
            if (sum_implicit_line == 0) draw_pixel(x, y, color);
        }
    }
}
