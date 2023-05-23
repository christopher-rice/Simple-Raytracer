#include "my_vector.h"

// Constructor
my_vector::my_vector(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

// X-component getter
float my_vector::get_x() 
{
	return(this->x);
}

// X-component setter
void my_vector::set_x(float x)
{
	this->x = x;
}

// Y-component getter
float my_vector::get_y()
{
	return(this->y);
}

// Y-component setter
void my_vector::set_y(float y)
{
	this->y = y;
}

// Z-component getter
float my_vector::get_z()
{
	return(this->z);
}

// Z-component setter
void my_vector::set_z(float z)
{
	this->z = z;
}

// W-component getter
float my_vector::get_w()
{
	return(this->w);
}

// W-component setter
void my_vector::set_w(float w)
{
	this->w = w;
}
