/** math.hpp **/

#ifndef STRF_MATH_HPP
#define STRF_MATH_HPP

#include <strf/global.hpp>

#define PI 3.14159265

#define strfmin(x,y) ((x) < (y) ? (x) : (y))
#define strfmax(x,y) ((x) > (y) ? (x) : (y))
#define strfclamp(x,y,z) ((x) < (y) ? (y) : ((x) > (z) ? (z) : (x)))

DLL_EXPORT int DLL_CALL randomi(cint bottom, cint top);
DLL_EXPORT float DLL_CALL randomf(cfloat bottom, cfloat top);
DLL_EXPORT double DLL_CALL randomd(cdouble bottom, cdouble top);
DLL_EXPORT int DLL_CALL mini(cint value, cint min);
DLL_EXPORT float DLL_CALL minf(cfloat value, cfloat min);
DLL_EXPORT double DLL_CALL mind(cdouble value, cdouble min);
DLL_EXPORT int DLL_CALL maxi(cint value, cint max);
DLL_EXPORT float DLL_CALL maxf(cfloat value, cfloat max);
DLL_EXPORT double DLL_CALL maxd(cdouble value, cdouble max);
DLL_EXPORT int DLL_CALL clampi(cint value, cint min, cint max);
DLL_EXPORT float DLL_CALL clampf(cfloat value, cfloat min, cfloat max);
DLL_EXPORT double DLL_CALL clampd(cdouble value, cdouble min, cdouble max);
DLL_EXPORT int DLL_CALL wrapi(int value, cint min, cint max);
DLL_EXPORT float DLL_CALL wrapf(float value, cfloat min, cfloat max);
DLL_EXPORT double DLL_CALL wrapd(double value, cdouble min, cdouble max);
DLL_EXPORT float DLL_CALL calc_distance(cfloat x1, cfloat y1, cfloat x2, cfloat y2);
DLL_EXPORT float DLL_CALL calc_distance_fast(cfloat x1, cfloat y1, cfloat x2, cfloat y2);
DLL_EXPORT float DLL_CALL mix(cfloat x1, cfloat x2, cfloat x);
DLL_EXPORT float DLL_CALL mix(cfloat x1, cfloat x2, cfloat y1, cfloat y2, cfloat x);
DLL_EXPORT float DLL_CALL calc_angle(cfloat x1, cfloat y1, cfloat x2, cfloat y2);
DLL_EXPORT bool DLL_CALL is_power_of_two(cuint value);
DLL_EXPORT float DLL_CALL point_distance_from_line(cfloat x, cfloat y, cfloat x1, cfloat y1, cfloat x2, cfloat y2);
DLL_EXPORT double DLL_CALL smooth_transition(cdouble value);
DLL_EXPORT void DLL_CALL get_hue(float &r, float &g, float &b, double value);  // 0 - 2 - 4 -      ->  r - g - b -
DLL_EXPORT void DLL_CALL get_hue2(float &r, float &g, float &b, double value); // 0 - 2 - 4 - 6 -  ->  r - y - g - b -
DLL_EXPORT float DLL_CALL b_spline(cfloat x1, cfloat x2, cfloat x3, cfloat x4, cfloat x);
DLL_EXPORT float DLL_CALL catmull_rom(cfloat x1, cfloat x2, cfloat x3, cfloat x4, cfloat t, cfloat x);

#endif
