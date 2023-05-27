#include "sphere.h"

// Constructor
sphere::sphere(point center, float radius)
{
	this->center = center;
	this->radius = radius;
}

// Center getter
point sphere::get_center() const
{
	return(center);
}

// Center setter
void sphere::set_center(const point& center)
{
	this->center = center;
}

// Radius getter
float sphere::get_radius() const
{
	return(radius);
}

// Radius setter
void sphere::set_radius(float radius)
{
	this->radius = radius;
}

// Checks if ray intersects with sphere (ASSUMES RAY ORIGINATES FROM ORIGIN
bool sphere::ray_sphere_intersect_test(
	const my_vector& vec        // Ray doing the intersection (must be normalized)
)
{
	// Gets vector from origin (camera location) to center of sphere
	my_vector OriginToCenter = this->get_center();

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
	my_vector dist_vec = proj_vec - this->get_center();

	// Intersection occurs if the radius is greater than or equal to the length of the distance vector
	return(dist_vec.get_length() <= this->get_radius());
}