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
float my_vector::get_x() const
{
	return(this->x);
}

// X-component setter
void my_vector::set_x(float x)
{
	this->x = x;
}

// Y-component getter
float my_vector::get_y() const
{
	return(this->y);
}

// Y-component setter
void my_vector::set_y(float y)
{
	this->y = y;
}

// Z-component getter
float my_vector::get_z() const
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

// Adding two vectors
my_vector my_vector::operator+(const my_vector& vec) const
{
	float new_x = this->get_x() + vec.get_x();
	float new_y = this->get_y() + vec.get_y();
	float new_z = this->get_z() + vec.get_z();

	return(my_vector(new_x, new_y, new_z));
}

// Subtracting two vectors
my_vector my_vector::operator-(const my_vector& vec) const
{
	float new_x = this->get_x() - vec.get_x();
	float new_y = this->get_y() - vec.get_y();
	float new_z = this->get_z() - vec.get_z();

	return(my_vector(new_x, new_y, new_z));
}

// Dot product of two vectors
float my_vector::operator*(const my_vector& vec) const
{
	return((this->get_x() * vec.get_x()) + (this->get_y() * vec.get_y()) + (this->get_z() * vec.get_z()));
}

// Length getter
float my_vector::get_length() const
{
	return(sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z)));
}

// Squared length getter
float my_vector::get_length_squared() const
{
	return((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

// Scalar multiplication
my_vector operator*(const my_vector& vec, float scalar)
{
	float new_x = scalar * vec.get_x();
	float new_y = scalar * vec.get_y();
	float new_z = scalar * vec.get_z();

	return(my_vector(new_x, new_y, new_z));
}

// Scalar multiplication with vector (scalar first)
my_vector operator*(float scalar, const my_vector& vec)
{
	float new_x = scalar * vec.get_x();
	float new_y = scalar * vec.get_y();
	float new_z = scalar * vec.get_z();

	return(my_vector(new_x, new_y, new_z));
}
