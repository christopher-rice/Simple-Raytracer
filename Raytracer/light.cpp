#include "light.h"

// Constructor
light::light(point position, float intensity)
{
	this->position = position;
	this->intensity = intensity;
}

// Position getter
point light::get_position() const
{
	return(this->position);
}

// Position setter
void light::set_position(const point& position)
{
	this->position = position;
}

// Intensity getter
float light::get_intensity() const
{
	return(this->intensity);
}

// Intensity setter
void light::set_intensity(float intensity)
{
	this->intensity = intensity;
}