#pragma once
#include <math.h>


class Mathlib
{
public:
	// Round for n digits (1-4)
	static double round_digits(double value, int place) {

		if (place == 1)	value = floor(value * 10 + 0.5) / 10;		// example: 2.6
		if (place == 2)	value = floor(value * 100 + 0.5) / 100;		// example: 2.56
		if (place == 3)	value = floor(value * 1000.0 + 0.5) / 1000;
		if (place == 4)	value = floor(value * 10000.0 + 0.5) / 10000;

		return value;
	}

	// Compares two values and returns the difference
	static double abs_difference(double value1, double value2){

		return fabs(value1 - value2);
	}
};



