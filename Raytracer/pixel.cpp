#include "pixel.h"

// Constructor
pixel::pixel(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

// Red-component getter
float pixel::get_red() const
{
	return(this->red);
}

// Red-component setter
void pixel::set_red(float red)
{
	this->red = red;
}

// Green-component getter
float pixel::get_green() const
{
	return(this->green);
}

// Green-component setter
void pixel::set_green(float green)
{
	this->green = green;
}

// Blue-component getter
float pixel::get_blue() const
{
	return(this->blue);
}

// Blue-component setter
void pixel::set_blue(float blue)
{
	this->blue = blue;
}

// Sets full RGB
void pixel::set_rgb(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}