#include "material.h"

material::material(const pixel& diffuse_color,
	float specular_index,
	float diffuse_albedo,
	float specular_albedo)
{
	this->diffuse_color = diffuse_color;
	this->specular_index = specular_index;
	this->diffuse_albedo = diffuse_albedo;
	this->specular_albedo = specular_albedo;
}

// Diffuse color getter
pixel material::get_diffuse_color() const
{
	return(this->diffuse_color);
}

// Diffuse color setter
void material::set_diffuse_color(const pixel& diffuse_color)
{
	this->diffuse_color = diffuse_color;
}

// Specular index getter
float material::get_specular_index() const
{
	return(this->specular_index);
}

// Specular index setter
void material::set_specular_index(float specular_index) 
{
	this->specular_index = specular_index;
}

// Diffuse albedo getter
float material::get_diffuse_albedo() const
{
	return(this->diffuse_albedo);
}

// Diffuse albedo setter
void material::set_diffuse_albedo(float diffuse_albedo)
{
	this->diffuse_albedo = diffuse_albedo;
}

// Specular albedo getter
float material::get_specular_albedo() const
{
	return(this->specular_albedo);
}

// Specular albedo setter
void material::set_specular_albedo(float specular_albedo)
{
	this->specular_albedo = specular_albedo;
}