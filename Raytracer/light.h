#pragma once

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "my_vector.h"

class light
{
private:
	point position;		// Represents the position of the light in 3D space
	float intensity;	// Represents the brightness of the light

public:
	// Constructor
	light(point position = point(0.0f, 0.0f, 0.0f), float intensity = 1.0f);

	// Position getter
	point get_position() const;

	// Position setter
	void set_position(const point& position);

	// Intensity getter
	float get_intensity() const;

	// Intensity setter
	void set_intensity(float intensity);
};

#endif
