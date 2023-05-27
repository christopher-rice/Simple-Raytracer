#include "sphere.h"

// Constructor
sphere::sphere(const point& center, float radius, const pixel& color)
{
	this->center = center;
	this->radius = radius;
	this->color = color;
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

// Color getter
pixel sphere::get_color() const
{
	return(color);
}

// Color setter
void sphere::set_color(const pixel& color)
{
	this->color = color;
}

// Checks if ray intersects with sphere (ASSUMES RAY ORIGINATES FROM ORIGIN
bool sphere::ray_sphere_intersect_test (
	const my_vector& vec,        // Ray doing the intersection (must be normalized)
	point& hit,					 // Point where the ray hits the sphere
	my_vector& normal_vec_norm   // Vector normal to surface
) const
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
	bool hit_check = dist_vec.get_length() <= this->get_radius();

	if (hit_check)
	{
		// Length of vector from center of circle to tip of projection squared
		float dist_vec_length_squared = dist_vec.get_length_squared();

		// Length of projection vector
		float proj_vec_length = proj_vec.get_length();

		// Calculates hit point
		hit = vec * (proj_vec_length - sqrtf(radius * radius - dist_vec_length_squared));

		// Calculates the normal to the surface
		normal_vec_norm = (hit - center).normalize();

		return(hit_check);
	}

	return(hit_check);
}

// Calculates the diffuse light component
pixel sphere::light_diffuse_calc(
	const light& light, 
	const my_vector& normal_vec_norm, 
	const my_vector& light_vec_norm
) const
{
	return(color * (light.get_intensity() * (normal_vec_norm * light_vec_norm)));
}

// Calculates the specular light component
pixel sphere::light_specular_calc(
	const light& light, 
	const my_vector& eye_vec_norm, 
	const my_vector& reflect_vec_norm
) const
{
	return(color * (light.get_intensity() * (eye_vec_norm * reflect_vec_norm)));
}