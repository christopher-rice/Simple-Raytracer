#pragma once

#ifndef __MY_VECTOR_H__
#define __MY_VECTOR_H__

#include <iostream>
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

    // Adding two vectors
    my_vector operator+(const my_vector& vec);

    // Subtracting two vectors
    my_vector operator-(const my_vector& vec);

    // Overload for output
    friend ostream& operator<<(ostream& output, const my_vector& vec)
    {
        output << "<" << vec.get_x() << ", " << vec.get_y() << ", " << vec.get_z() << ">";
        return output;
    }
};

typedef my_vector point;

#endif