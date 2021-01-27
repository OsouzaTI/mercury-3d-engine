#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vector.h"
#include "matrix.h"
#include "drawing.h"
#include "texture.h"

typedef struct {
    float u;
    float v;
} UVtext;

typedef struct {
    int a;
    int b;
    int c;
    UVtext a_uv;
    UVtext b_uv;
    UVtext c_uv;
    uint32_t color;
} face;


typedef struct {
    vect2<float> points[3];
    UVtext textcoords[3];
    uint32_t color;
    float avg_depth;

} triangle;

typedef struct
{
    std::vector<vect3<float>> vertices;
    std::vector<face> faces;
    vect3<float> scale;
    vect3<float> rotation;
    vect3<float> translation;
} mesh_t;

class Mesh
{
    public:
        Mesh();
        ~Mesh();
        bool loaded;

        mesh_t mesh;
        std::vector<triangle> triangles_to_render;
        
        void load_cube_object();
        void load_obj_file_data(char* filename);        
        void update_mesh();
        void draw_mesh();

        void set_display(Display* display);
        void set_color(uint32_t color);
        void set_drawing(Drawing* drawing);
        uint32_t get_color();

        void set_translation(vect3<float> translation);
        void set_scale(vect3<float> scale);
        void set_rotate(vect3<float> rotation);
        void set_shearXY(float angle);
        void set_shearYX(float angle);
        
        vect3<float>* get_translation();
        vect3<float>* get_scale();
        vect3<float>* get_rotate();


        void set_rotate_mesh_x(float angle_x);
        void set_rotate_mesh_y(float angle_y);
        void set_rotate_mesh_z(float angle_z);
    private:        
        Display* display;
        Drawing* draw;
        vect3<float> cube_vertices[8];
        face cube_faces[12];
        uint32_t color = C_WHITE;
        Mat4x4 shearXY_matrix;
        Mat4x4 shearYX_matrix;
};

#endif