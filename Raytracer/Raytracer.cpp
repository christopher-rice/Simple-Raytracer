#include <limits>       // Contains limit values to integral types
#include <cmath>        // Contains several functions for math operations
#include <iostream>     // Contains functions for terminal I/O
#include <fstream>      // Contains functions for file I/O
#include <vector>       // Contains implementation for vector

#include "my_vector.h"
#include "pixel.h"
#include "sphere.h"

using namespace std;

// Value of pi
const float pi = 3.141592741012573242187500;

// Sphere within 3D space
sphere sphere1(point(0.0f, 0.0f, -5.0f), 2.0f);

// Colors for background and sphere
pixel background_color(0.0f, 0.0f, 0.0f);
pixel sphere_color(0.0f, 0.0f, 1.0f);

// Checks if ray intersects with sphere (ASSUMES RAY ORIGINATES FROM ORIGIN
bool ray_sphere_intersect_test(
    const sphere& sphere,       // Sphere to be intersected
    const my_vector& vec        // Ray doing the intersection (must be normalized)
)
{
    // Gets vector from origin (camera location) to center of sphere
    my_vector OriginToCenter = sphere.get_center();

    // Finds dot product between ray and vector to center of sphere
    float dot_prod = vec * OriginToCenter;

    // If the ray and vector to center of sphere are facing opposite directions then intersection isn't possible
    if (dot_prod < 0)
    {
        return(false);
    }

    // Finds projection of vector to center of sphere on to ray
    my_vector proj_vec = vec * dot_prod;

    // Finds vector from center of sphere to tip of projection
    my_vector dist_vec = proj_vec - sphere.get_center();

    // Intersection occurs if the radius is greater than or equal to the length of the distance vector
    return(dist_vec.get_length() <= sphere.get_radius());
}

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

            // Tests if view vector intersects with sphere
            bool is_intersect = ray_sphere_intersect_test(sphere1, view_vec_norm);

            // Puts color to frame buffer depending on intersection or not
            if (is_intersect)
            {
                frame_buffer[j + i * width] = sphere_color;
            }
            else
            {
                frame_buffer[j + i * width] = background_color;
            }
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
    render();
    cout << "Raytracing End" << endl;

    return(0);
}


