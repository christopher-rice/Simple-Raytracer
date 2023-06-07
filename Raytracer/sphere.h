#pragma once

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "my_vector.h"
#include "pixel.h"
#include "light.h"
#include "material.h"

class sphere
{
private:
	point center;				// Point that represents 3D position of center of sphere
	float radius;				// Radius of the sphere
	material mat;				// Material of the sphere

public:
	// Constructor
	sphere(const point& center = point(0.0f, 0.0f, 0.0f), 
		   float radius = 1.0f,
		   const material& mat = material());

	// Center getter
	point get_center() const;

	// Center setter
	void set_center(const point& center);

	// Radius getter
	float get_radius() const;

	// Radius setter
	void set_radius(float radius);

	// Material getter
	material get_material() const;

	// Material setter
	void set_material(const material& mat);

	// Checks if ray intersects with sphere (Default argument assumes ray starts from origin)
	bool ray_sphere_intersect_test(const my_vector& vec, 
								   point& hit, 
								   my_vector& normal_vec_norm,
								   const point& origin = point(0.0f, 0.0f, 0.0f)) const;

	// Calculates the diffuse light component
	pixel light_diffuse_calc(const light& light, const my_vector& normal_vec_norm, const my_vector& light_vec_norm) const;

	// Calculates the specular light component
	pixel light_specular_calc(const light& light, const my_vector& eye_vec_norm, const my_vector& reflect_vec_norm) const;

	// Calculates the ambient light component
	pixel light_ambient_calc(float ambient_light) const;

	// Overload for output
	friend ostream& operator<<(ostream& output, const sphere& sphere)
	{
		output << "Center = <" << sphere.center.get_x() << ", " << sphere.center.get_y() << ", " << sphere.center.get_z() << "> ";
		output << "Radius = " << sphere.radius << " ";
		return output;
	}
};

#endif