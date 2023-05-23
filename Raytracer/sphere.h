#pragma once

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "my_vector.h"

class sphere
{
private:
	point center;	// Point that represents 3D position of center of sphere
	float radius;	// The radius of the sphere

public:
	// Constructor
	sphere(point center = point(0.0f, 0.0f, 0.0f), float radius = 1.0f);

	// Center getter
	point get_center() const;

	// Center setter
	void set_center(const point& center);

	// Radius getter
	float get_radius() const;

	// Radius setter
	void set_radius(float radius);
};

#endif