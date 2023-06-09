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
const float pi = 3.141592741012573242187500f;

// Value to make sure rays don't intersect with the geometry they originate from
const float epsilon = 0.001f;

// Colors for background and sphere
pixel background_color(0.0f, 0.0f, 0.0f);

// Ambient light intensity (ranges from 0 to 1)
float ambient_light_intensity = 0.15;

// Checks if a point is in shadow for a light
bool shadow_check(const light& current_light, 
                  const point& hit, 
                  const vector<sphere>& geometry_vec, 
                  int curr_sphere_index)
{
    // Indicates if current point is in shadow
    bool is_shadow;

    // Normalized vector from hit to other sphere
    my_vector shadow_check_vec_norm = (current_light.get_position() - hit).normalize();

    // Origin of vector from hit to other sphere with a little bit of epsilon added
    point shadow_check_vec_origin = hit + (shadow_check_vec_norm * epsilon);

    // Point where check hits and normal vector on surface
    point shadow_check_hit;
    my_vector shadow_check_normal_norm;

    // Checks if there is any geometry blocking the light
    for (int k = 0; k < geometry_vec.size(); k++)
    {
        is_shadow = geometry_vec[k].ray_sphere_intersect_test(shadow_check_vec_norm, shadow_check_hit, shadow_check_normal_norm, shadow_check_vec_origin);

        if ((k != curr_sphere_index) && is_shadow)
        {
            break;
        }

        is_shadow = false;
    }

    return(is_shadow);
}

// Sends a ray out into the scene
pixel ray_cast(const my_vector& view_vec_norm,
               const vector<sphere>& geometry_vec,
               const vector<light>& light_vec,
               int depth = 0,
               const point& origin = point(0.0f, 0.0f, 0.0f))
{
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
        hit_check = geometry_vec[i].ray_sphere_intersect_test(view_vec_norm, hit, normal_vec_norm, origin);

        // Gets color from sphere if hit occurs
        if (hit_check)
        {
            // Sets default colors
            drawn_pixel = pixel(0.0f, 0.0f, 0.0f);
            pixel diffuse_color = pixel(0.0f, 0.0f, 0.0f);
            pixel specular_color = pixel(0.0f, 0.0f, 0.0f);

            // Gets normalized vector to camera 
            eye_vec_norm = (origin - hit).normalize();

            // Calculates incidence of light at hit
            for (int j = 0; j < light_vec.size(); j++)
            {
                // Indicates if point is in shadow
                bool is_shadow = shadow_check(light_vec[j], hit, geometry_vec, i);

                // Does light calculations if not in shadow
                if (is_shadow)
                {
                    continue;
                }

                // Gets normalized vector to light
                light_vec_norm = (light_vec[j].get_position() - hit).normalize();

                // Gets reflected vector to light
                reflect_vec_norm = (2 * (light_vec_norm * normal_vec_norm) * normal_vec_norm - light_vec_norm).normalize();

                // Calculating diffuse and specular light
                diffuse_color = geometry_vec[i].light_diffuse_calc(light_vec[j], normal_vec_norm, light_vec_norm);
                specular_color = geometry_vec[i].light_specular_calc(light_vec[j], eye_vec_norm, reflect_vec_norm);

                // Adding diffuse and specular light intensities
                drawn_pixel = drawn_pixel + diffuse_color + specular_color;
            }

            // Gets view vector reflected across the normal
            my_vector view_reflect_vec_norm = (2 * (eye_vec_norm * normal_vec_norm) * normal_vec_norm - eye_vec_norm).normalize();

            // Calculating color from reflection and refraction
            pixel reflected_color;
            pixel refraction_color;

            if (depth <= 4)
            {
                reflected_color = ray_cast(view_reflect_vec_norm, geometry_vec, light_vec, depth + 1, hit);
            }

            drawn_pixel = drawn_pixel + reflected_color * geometry_vec[i].get_material().get_reflection_albedo();

            // Calculating ambient light
            drawn_pixel = drawn_pixel + geometry_vec[i].light_ambient_calc(ambient_light_intensity);

            // Exits from loop with first hit
            break;
        }
    }

    return(drawn_pixel);
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

    // Vector that will contain all lights within the scene
    vector<light> light_vec = {
        light(point(-5.0f, 3.0f, 0.0f), 0.3f),
        light(point(5.0f, -1.0f, 0.0f), 0.3f)
    };

    // Vector that contains all geometry in the scene
    vector<sphere> geometry_vec = {
        sphere(point(-2.0f, 1.0f, -5.0f), 0.5f, material(pixel(0.0f, 0.0f, 1.0f), 1.0f, 1.0f, 1.0f, 0.7f)),
        sphere(point(-2.0f, -1.0f, -5.0f), 0.6f, material(pixel(1.0f, 0.0f, 1.0f), 3.0f, 1.0f, 1.0f, 0.5f)),
        sphere(point(2.0f, 1.0f, -5.0f), 0.7f, material(pixel(1.0f, 0.0f, 0.0f), 5.0f, 1.0f, 1.0f, 0.3f)),
        sphere(point(2.0f, -1.0f, -5.0f), 0.3f, material(pixel(1.0f, 1.0f, 0.0f), 7.0f, 1.0f, 1.0f, 0.1f)),
        sphere(point(0.0f, 0.0f, -5.0f), 1.0f, material(pixel(1.0f, 1.0f, 1.0f), 10.0f, 0.2f, 1.0f, 1.0f))
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

            // Casts ray in and gets color back
            pixel drawn_pixel = ray_cast(view_vec_norm, geometry_vec, light_vec);

            // Caps the colors of the pixel
            drawn_pixel.cap_rgb();

            // Draws color to pixel buffer
            frame_buffer[j + i * width] = drawn_pixel;
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


