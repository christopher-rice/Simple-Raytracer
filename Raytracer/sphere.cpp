#include "sphere.h"

// Constructor
sphere::sphere(const point& center, 
			   float radius,
			   const material& mat)
{
	this->mat = mat;
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

// Material getter
material sphere::get_material() const
{
	return(mat);
}

// Material setter
void sphere::set_material(const material& mat)
{
	this->mat = mat;
}

// Checks if ray intersects with sphere (ASSUMES RAY ORIGINATES FROM ORIGIN
bool sphere::ray_sphere_intersect_test (
	const my_vector& vec_norm,        // Ray doing the intersection (must be normalized)
	point& hit,					 // Point where the ray hits the sphere
	my_vector& normal_vec_norm,  // Vector normal to surface
	const point& origin			 // Starting point of the ray
) const
{
	// Gets vector from origin of ray to center of sphere
	my_vector origin_to_center = this->get_center() - origin;

	// Finds dot product between ray and vector to center of sphere
	float dot_prod = vec_norm * origin_to_center;

	// If the ray and vector to center of sphere are facing opposite directions then intersection isn't possible
	if (dot_prod < 0)
	{
		return(false);
	}

	// Finds projection of vector to center of sphere on to ray
	my_vector proj_vec = vec_norm * dot_prod;

	// Finds vector from center of sphere to tip of projection
	my_vector dist_vec = proj_vec - origin_to_center;

	// Intersection occurs if the radius is greater than or equal to the length of the distance vector
	bool hit_check = dist_vec.get_length() <= this->get_radius();

	if (hit_check)
	{
		// Length of vector from center of circle to tip of projection squared
		float dist_vec_length_squared = dist_vec.get_length_squared();

		// Length of projection vector
		float proj_vec_length = proj_vec.get_length();

		// Calculates hit point
		hit = origin + vec_norm * (proj_vec_length - sqrtf(radius * radius - dist_vec_length_squared));

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
	return(mat.get_diffuse_color() * mat.get_diffuse_albedo() * (light.get_intensity() * max(normal_vec_norm * light_vec_norm, 0.0f)));
}

// Calculates the specular light component
pixel sphere::light_specular_calc(
	const light& light, 
	const my_vector& eye_vec_norm, 
	const my_vector& reflect_vec_norm
) const
{
	return(pixel(1.0f, 1.0f, 1.0f) * mat.get_specular_albedo() *(light.get_intensity() * powf(max(eye_vec_norm * reflect_vec_norm, 0.0f), mat.get_specular_index())));
}

// Calculates the ambient light component
pixel sphere::light_ambient_calc(float ambient_light) const
{
	return(mat.get_diffuse_color() * ambient_light * mat.get_diffuse_albedo());
}