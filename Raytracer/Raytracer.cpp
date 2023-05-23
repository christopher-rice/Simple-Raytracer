#include <limits>       // Contains limit values to integral types
#include <cmath>        // Contains several functions for math operations
#include <iostream>     // Contains functions for terminal I/O
#include <fstream>      // Contains functions for file I/O
#include <vector>       // Contains implementation for vector

#include "my_vector.h"
#include "pixel.h"

using namespace std;

// Value of pi
const double pi = 3.14159265358979323846;

// Sphere representation
struct sphere
{
    my_vector center;       // Location of the center of the sphere
    float radius = 0.0f;    // Radius of the circle
};

// Checks if ray intersects with sphere
/*
bool ray_sphere_intersect_test(
    my_vector ray_origin,       // Vector representing the origin of the ray
    my_vector ray_direction,    // Vector representing the direction of the ray
    my_vector sphere_center,    // Vector representing the position of the center of the sphere
    float sphere_radius         // The radius of the sphere
)
{

}
*/

// Renders the image to the frame buffer
void render()
{
    // Width and height of the pic in pixels
    const int width = 800;
    const int height = 600;

    // FOV and aspect ratio of the camera
    const float fov = 60.0f;
    float aspect_ratio = width / float(height);

    // Vector that contains all pixels in the pic
    vector<pixel> frame_buffer(width * height);

    // Looping through all the pixels in the frame buffer
    for (size_t i = 0; i < height; i++) 
    {
        for (size_t j = 0; j < width; j++)
        {
            // Calculating the x and y coordinates of the view vector
            float x_view = tanf((fov / 2) * (pi / 180)) * ((2.0f * j + 1.0f - width) / width);
            float y_view = -1.0f * tanf((fov / (2 * aspect_ratio)) * (pi / 180)) * ((2.0f * i + 1.0f - height) / height);
            
            // Creating the normalized view vector
            my_vector view_vec(x_view, y_view, -1.0f, 1.0f);
            my_vector view_vec_norm = view_vec.normalize();

            frame_buffer[j + i * width].set_rgb(i / float(height), j / float(width), 0.0f);
        }
    }

    // Creating an output file
    ofstream ofs("image.ppm");

    // Initial ppm info
    ofs << "P3\n";
    ofs << width << "\n";
    ofs << height << "\n";
    ofs << "255\n";

    // Looping through pixels in frame buffer
    for (size_t i = 0; i < width * height; i++)
    {
        ofs << int(255 * frame_buffer[i].get_red()) << " ";
        ofs << int(255 * frame_buffer[i].get_green()) << " ";
        ofs << int(255 * frame_buffer[i].get_blue()) << "\n";
    }

    // Closing file
    ofs.close();
}

int main()
{
    cout << "Raytracing Start" << endl;
    //render();

    my_vector vec1(1.0f, 2.0f, 3.0f);
    my_vector norm_vec = vec1.normalize();
    cout << "The normalized vector of " << vec1 << " is " << norm_vec << endl;

    cout << "Raytracing End" << endl;

    return(0);
}


