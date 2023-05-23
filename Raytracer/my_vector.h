#pragma once

#ifndef __MY_VECTOR_H__
#define __MY_VECTOR_H__

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
    float get_x();

    // X-component setter
    void set_x(float x);

    // Y-component getter
    float get_y();

    // Y-component setter
    void set_y(float y);

    // Z-component getter
    float get_z();

    // Z-component setter
    void set_z(float z);

    // W-component getter
    float get_w();

    // W-component setter
    void set_w(float w);
};

typedef my_vector point;

#endif