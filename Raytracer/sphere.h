#pragma once

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "my_vector.h"
#include "pixel.h"
#include "light.h"

class sphere
{
private:
	point center;	// Point that represents 3D position of center of sphere
	float radius;	// The radius of the sphere
	pixel color;	// Color of the sphere

public:
	// Constructor
	sphere(const point& center = point(0.0f, 0.0f, 0.0f), float radius = 1.0f, const pixel& color = pixel(0.0f, 0.0f, 0.0f));

	// Center getter
	point get_center() const;

	// Center setter
	void set_center(const point& center);

	// Radius getter
	float get_radius() const;

	// Radius setter
	void set_radius(float radius);

	// Color getter
	pixel get_color() const;

	// Color setter
	void set_color(const pixel& color);

	// Checks if ray intersects with sphere (ASSUMES RAY ORIGINATES FROM ORIGIN
	bool ray_sphere_intersect_test(const my_vector& vec, point& hit) const;

	// Calculates the incidence of specific light on specific point
	float light_incidence_calc(const point& hit, const light& light) const;

	// Overload for output
	friend ostream& operator<<(ostream& output, const sphere& sphere)
	{
		output << "Center = <" << sphere.center.get_x() << ", " << sphere.center.get_y() << ", " << sphere.center.get_z() << "> ";
		output << "Radius = " << sphere.radius << " ";
		return output;
	}
};

#endif