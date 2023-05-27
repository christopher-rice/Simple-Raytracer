#pragma once

#ifndef __PIXEL_H__
#define __PIXEL_H__

class pixel
{
private:
	float red;
	float green;
	float blue;

public:
    // Constructor
    pixel(float red = 0.0f, float green = 0.0f, float blue = 0.0f);

    // Red-component getter
    float get_red() const;

    // Red-component setter
    void set_red(float red);

    // Green-component getter
    float get_green() const;

    // Green-component setter
    void set_green(float green);

    // Blue-component getter
    float get_blue() const;

    // Blue-component setter
    void set_blue(float blue);

    // Sets full RGB
    void set_rgb(float red, float green, float blue);
};

#endif