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

// Caps RGB
void pixel::cap_rgb()
{
	if (red < 0.0f)
	{
		red = 0.0f;
	}
	else if (red > 1.0f)
	{
		red = 1.0f;
	}

	if (green < 0.0f)
	{
		green = 0.0f;
	}
	else if (green > 1.0f)
	{
		green = 1.0f;
	}

	if (blue < 0.0f)
	{
		blue = 0.0f;
	}
	else if (blue > 1.0f)
	{
		blue = 1.0f;
	}
}

// Adding two pixels
pixel pixel::operator+(const pixel & pix) const
{
	float new_red = this->red + pix.get_red();
	float new_green = this->green + pix.get_green();
	float new_blue = this->blue + pix.get_blue();

	return(pixel(new_red, new_green, new_blue));
}

// Multiplying a pixel and a scalar (pixel first)
pixel operator*(const pixel& pix, float scalar)
{
	float new_red = pix.get_red() * scalar;
	float new_green = pix.get_green() * scalar;
	float new_blue = pix.get_blue() * scalar;

	return(pixel(new_red, new_green, new_blue));
}

// Multiplying a pixel and a scalar (scalar first)
pixel operator*(float scalar, const pixel& pix)
{
	float new_red = pix.get_red() * scalar;
	float new_green = pix.get_green() * scalar;
	float new_blue = pix.get_blue() * scalar;

	return(pixel(new_red, new_green, new_blue));
}
