#pragma once

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "pixel.h"

class material
{
private:
	pixel diffuse_color;
	float specular_index;
	float diffuse_albedo;
	float specular_albedo;
public:
	// Material constructor
	material(const pixel& diffuse_color = pixel(),
			 float specular_index = 0.0f,
			 float diffuse_albedo = 0.0f,
			 float specular_albedo = 0.0f);

	// Diffuse color getter
	pixel get_diffuse_color() const;

	// Diffuse color setter
	void set_diffuse_color(const pixel& diffuse_color);

	// Specular index getter
	float get_specular_index() const;

	// Specular index setter
	void set_specular_index(float specular_index);

	// Diffuse albedo getter
	float get_diffuse_albedo() const;

	// Diffuse albedo setter
	void set_diffuse_albedo(float diffuse_albedo);

	// Specular albedo getter
	float get_specular_albedo() const;

	// Specular albedo setter
	void set_specular_albedo(float specular_albedo);
};

#endif