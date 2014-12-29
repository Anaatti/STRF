/** math.cpp **/

#include "global.hpp"
#include <cstdlib>
#include <cmath>

#define PI 3.14159265

DLL_EXPORT float DLL_CALL randomf(cfloat bottom, cfloat top) {
	return (float)rand() / (float)RAND_MAX * (top - bottom) + bottom;
}

DLL_EXPORT int DLL_CALL randomi(cint bottom, cint top) {
	int random;
	do {
		random = int(randomf(0, 1) * (top - bottom + 1) + bottom);
	} while(random > top);
	return random;
}

DLL_EXPORT double DLL_CALL randomd(cdouble bottom, cdouble top) {
	return (double)rand() / (double)RAND_MAX * (top - bottom) + bottom;
}

DLL_EXPORT int DLL_CALL mini(cint value, cint min) {
	return value < min ? value : min;
}

DLL_EXPORT float DLL_CALL minf(cfloat value, cfloat min) {
	return value < min ? value : min;
}

DLL_EXPORT double DLL_CALL mind(cdouble value, cdouble min) {
	return value < min ? value : min;
}

DLL_EXPORT int DLL_CALL maxi(cint value, cint max) {
	return value > max ? value : max;
}

DLL_EXPORT float DLL_CALL maxf(cfloat value, cfloat max) {
	return value > max ? value : max;
}

DLL_EXPORT double DLL_CALL maxd(cdouble value, cdouble max) {
	return value > max ? value : max;
}

DLL_EXPORT int DLL_CALL clampi(cint value, cint min, cint max) {
	if(value < min) return min;
	else if(value > max) return max;
	else return value;
}

DLL_EXPORT float DLL_CALL clampf(cfloat value, cfloat min, cfloat max) {
	if(value < min) return min;
	else if(value > max) return max;
	else return value;
}

DLL_EXPORT double DLL_CALL clampd(cdouble value, cdouble min, cdouble max) {
	if(value < min) return min;
	else if(value > max) return max;
	else return value;
}

DLL_EXPORT int DLL_CALL wrapi(int value, cint min, cint max) {
	if(max < min) return min;
	value = (value - min) % (max - min + 1);
	return value + (value < 0 ? (max - min + 1) : 0) + min;
}

DLL_EXPORT float DLL_CALL wrapf(float value, cfloat min, cfloat max) {
	if(max < min) return min;
	//return fmod(value - min, max - min) + min;
	cfloat delta = max - min;
	while(value > max) value-= delta;
	while(value < min) value+= delta;
	return value;
}

DLL_EXPORT double DLL_CALL wrapd(double value, cdouble min, cdouble max) {
	if(max < min) return min;
	//return fmod(value - min, max - min) + min;
	cdouble delta = max - min;
	while(value > max) value-= delta;
	while(value < min) value+= delta;
	return value;
}

DLL_EXPORT float DLL_CALL calc_distance(cfloat x1, cfloat y1, cfloat x2, cfloat y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

DLL_EXPORT float DLL_CALL calc_distance_fast(cfloat x1, cfloat y1, cfloat x2, cfloat y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

DLL_EXPORT float DLL_CALL mix(cfloat x1, cfloat x2, cfloat x) {
	return (x2 - x1) * x + x1;
}

DLL_EXPORT float DLL_CALL mix(cfloat x1, cfloat x2, cfloat y1, cfloat y2, cfloat x) {
	return (y1 - y2) / (x1 - x2) * (x - x1) + y1;
}

DLL_EXPORT float DLL_CALL calc_angle(cfloat x1, cfloat y1, cfloat x2, cfloat y2) {
	return atan2(y2 - y1, x2 - x1);
}

DLL_EXPORT bool DLL_CALL is_power_of_two(cuint value) {
	return !(value & (value - 1)) && value;
}

DLL_EXPORT float DLL_CALL point_distance_from_line(cfloat x, cfloat y, cfloat x1, cfloat y1, cfloat x2, cfloat y2) {
	if(x1 == x2) return fabs(x - x1);
	cfloat a = (y1 - y2) / (x2 - x1);
	cfloat c = (y2 - y1) * x1 / (x2 - x1) - y1;
	return fabs(a * x + y + c) / sqrt(a * a + 1);
}

DLL_EXPORT double DLL_CALL smooth_transition(cdouble value) {
	return 0.5 - 0.5 * cos(value * PI);
}

DLL_EXPORT void DLL_CALL get_hue(float &r, float &g, float &b, double value) {
	value = ((value / 6.0) - floor(value / 6.0)) * 6.0;
	if(value < 1.0 || value > 5.0) r = 1.0;
	else if(value < 2.0) r = 2.0 - value;
	else if(value > 4.0) r = value - 4.0;
	else r = 0.0;
	if(value < 1.0) g = value;
	else if(value < 3.0) g = 1.0;
	else if(value < 4.0) g = 4.0 - value;
	else g = 0.0;
	if(value > 5.0) b = 6.0 - value;
	else if(value > 3.0) b = 1.0;
	else if(value > 2.0) b = value - 2.0;
	else b = 0.0;
}

DLL_EXPORT void DLL_CALL get_hue2(float &r, float &g, float &b, double value) {
	value = ((value / 8.0) - floor(value / 8.0)) * 8.0;
	if(value < 2.0 || value > 7.0) r = 1.0;
	else if(value < 4.0) r = 2.0 - value * 0.5;
	else if(value > 6.0) r = value - 6.0;
	else r = 0.0;
	if(value < 2.0) g = value * 0.5;
	else if(value < 5.0) g = 1.0;
	else if(value < 6.0) g = 6.0 - value;
	else g = 0.0;
	if(value > 7.0) b = 8.0 - value;
	else if(value > 5.0) b = 1.0;
	else if(value > 4.0) b = value - 4.0;
	else b = 0.0;
}

DLL_EXPORT float DLL_CALL b_spline(cfloat x1, cfloat x2, cfloat x3, cfloat x4, cfloat x) {
	return ((1.0 - x) * (1.0 - x) * (1.0 - x) * x1
		+ (3.0 * x * x * x - 6.0 * x * x + 4.0) * x2
		+ (-3.0 * x * x * x + 3.0 * x * x + 3.0 * x + 1.0) * x3
		+ x * x * x * x4) / 6.0;
}

DLL_EXPORT float DLL_CALL catmull_rom(cfloat x1, cfloat x2, cfloat x3, cfloat x4, cfloat t, cfloat x) {
	return (-t * x + 2.0 * t * x * x - t * x * x * x) * x1
		+ (1.0 + (t - 3.0) * x * x + (2.0 - t) * x * x * x) * x2
		+ (t * x + (3.0 - 2.0 * t) * x * x + (t - 2.0) * x * x * x) * x3
		+ (-t * x * x + t * x * x * x) * x4;
}
