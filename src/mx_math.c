#include "mx/mx_math.h"

float clampf(float val, float min, float max) {
	if(val < min) {
		return min;
	}

	if(val > max) {
		return max;
	}

	return val;
}

float lerpf(float a, float b, float t)  {
	return a * (1-t) + b * t;
}
