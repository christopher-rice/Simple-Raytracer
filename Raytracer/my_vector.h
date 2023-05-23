#pragma once

#ifndef __MY_VECTOR_H__
#define __MY_VECTOR_H__

#include <iostream>
#include <cmath>
using namespace std;

class my_vector
{
private:
    float x;     // X-component of the vector
    float y;     // Y-component of the vector
    float z;     // Z-component of the vector
    float w;     // W-component of the vector

public:
    // Constructor
    my_vector(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

    // X-component getter
    float get_x() const;

    // X-component setter
    void set_x(float x);

    // Y-component getter
    float get_y() const;

    // Y-component setter
    void set_y(float y);

    // Z-component getter
    float get_z() const;

    // Z-component setter
    void set_z(float z);

    // W-component getter
    float get_w();

    // W-component setter
    void set_w(float w);

    // Length getter
    float get_length() const;

    // Squared length getter
    float get_length_squared() const;

    // Returns a normalized vector
    my_vector normalize() const;

    // Adding two vectors
    my_vector operator+(const my_vector& vec) const;

    // Subtracting two vectors
    my_vector operator-(const my_vector& vec) const;

    // Dividing by scalar
    my_vector operator/(float scalar) const;

    // Dot product of two vectors
    float operator*(const my_vector& vec) const;

    // Overload for output
    friend ostream& operator<<(ostream& output, const my_vector& vec)
    {
        output << "<" << vec.get_x() << ", " << vec.get_y() << ", " << vec.get_z() << ">";
        return output;
    }
};

// Scalar multiplication (vector first)
my_vector operator*(const my_vector& vec, float scalar);

// Scalar multiplication with vector (scalar first)
my_vector operator*(float scalar, const my_vector& vec);

typedef my_vector point;

#endif