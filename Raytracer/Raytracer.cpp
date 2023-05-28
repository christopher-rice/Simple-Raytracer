#include <limits>       // Contains limit values to integral types
#include <cmath>        // Contains several functions for math operations
#include <iostream>     // Contains functions for terminal I/O
#include <fstream>      // Contains functions for file I/O
#include <vector>       // Contains implementation for vector

#include "my_vector.h"
#include "pixel.h"
#include "sphere.h"
#include "light.h"

using namespace std;

// Value of pi
const float pi = 3.141592741012573242187500;

// Colors for background and sphere
pixel background_color(0.0f, 0.0f, 0.0f);

// Ambient light intensity (ranges from 0 to 1)
float ambient_light_intensity = 0.15;

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

    // Vector that will contain all lights within the scene
    vector<light> light_vec = {
        light(point(-2.0f, 1.0f, 0.0f), 0.5f),
        //light(point(2.0f, -1.0f, 0.0f), 0.7f)
    };

    // Vector that contains all geometry in the scene
    vector<sphere> geometry_vec = {
        sphere(point(-2.0f, 1.0f, -5.0f), 0.5f, pixel(0.0f, 0.0f, 1.0f), pixel(1.0f, 1.0f, 1.0f), pixel(0.0f, 0.0f, 1.0f), 1.0f),
        sphere(point(2.0f, -1.0f, -5.0f), 0.7f, pixel(1.0f, 0.0f, 0.0f), pixel(1.0f, 1.0f, 1.0f), pixel(1.0f, 0.0f, 0.0f), 5.0f),
        sphere(point(0.0f, 0.0f, -5.0f), 1.0f, pixel(0.0f, 1.0f, 0.0f), pixel(1.0f, 1.0f, 1.0f), pixel(0.0f, 1.0f, 0.0f), 10.0f)
    };

    // Looping through all the pixels in the frame buffer
    for (size_t i = 0; i < height; i++) 
    {
        for (size_t j = 0; j < width; j++)
        {
            // Calculating the x and y coordinates of the view vector
            float x_view = tanf((fov / 2) * (pi / 180)) * ((2.0f * j + 1.0f - width) / width);
            float y_view = -1.0f * tanf((fov / (2 * aspect_ratio)) * (pi / 180)) * ((2.0f * i + 1.0f - height) / height);
            
            // Creating the normalized view vector
            my_vector view_vec_norm = my_vector(x_view, y_view, -1.0f, 1.0f).normalize();

            // Color of pixel to be drawn to screen
            pixel drawn_pixel = background_color;

            // Point and check for hit
            bool hit_check;
            point hit;

            // Vectors used for light calculations
            my_vector eye_vec_norm; // Vector from hit point to camera
            my_vector normal_vec_norm; // Vector normal to surface
            my_vector light_vec_norm; // Vector from hit point to light
            my_vector reflect_vec_norm; // Vector of light vector reflected across normal

            // Tests if view vector intersects with spheres
            for (int i = 0; i < geometry_vec.size(); i++)
            {
                // Performs ray-sphere intersection
                hit_check = geometry_vec[i].ray_sphere_intersect_test(view_vec_norm, hit, normal_vec_norm);

                // Gets color from sphere if hit occurs
                if (hit_check)
                {
                    // Resets color
                    drawn_pixel = pixel(0.0f, 0.0f, 0.0f);
                    
                    // Gets normalized vector to camera (Assumes camera is at origin
                    eye_vec_norm = (point() - hit).normalize();

                    // Calculates incidence of light at hit
                    for (int j = 0; j < light_vec.size(); j++)
                    {
                        // Gets normalized vector to light
                        light_vec_norm = (light_vec[j].get_position() - hit).normalize();

                        // Gets reflected vector to light
                        reflect_vec_norm = (2 * (light_vec_norm * normal_vec_norm) * normal_vec_norm - light_vec_norm).normalize();

                        // Calculating diffuse and specular light
                        //pixel diffuse_color = geometry_vec[i].light_diffuse_calc(light_vec[j], normal_vec_norm, light_vec_norm);
                        pixel specular_color = geometry_vec[i].light_specular_calc(light_vec[j], eye_vec_norm, reflect_vec_norm);

                        // Adding diffuse and specular light intensities
                        //drawn_pixel = drawn_pixel + diffuse_color; //+ specular_color;
                        drawn_pixel = drawn_pixel + specular_color;
                    }

                    //drawn_pixel = drawn_pixel + (geometry_vec[i].get_ambient_color() * ambient_light_intensity);

                    // Exits from loop with first hit
                    break;
                }
            }

            // Caps the colors of the pixel
            drawn_pixel.cap_rgb();

            // Draws color to pixel buffer
            frame_buffer[j + i * width] = drawn_pixel;

            //TEST
            //cout << drawn_pixel << endl;
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


