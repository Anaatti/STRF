/** draw.hpp **/

#ifndef STRF_DRAW_HPP
#define STRF_DRAW_HPP

#include <strf/texture.hpp>

namespace strf {
	extern DLL_EXPORT double top_edge;
	extern DLL_EXPORT double bottom_edge;
	extern DLL_EXPORT double left_edge;
	extern DLL_EXPORT double right_edge;

	DLL_EXPORT double DLL_CALL res_to_proj_x(cdouble value);
	DLL_EXPORT double DLL_CALL res_to_proj_y(cdouble value);
	DLL_EXPORT double DLL_CALL proj_to_res_x(cdouble value);
	DLL_EXPORT double DLL_CALL proj_to_res_y(cdouble value);
	DLL_EXPORT void DLL_CALL swap_frame();
	DLL_EXPORT void DLL_CALL poll_events();
	#ifndef STRF_INIT_HPP
	DLL_EXPORT void DLL_CALL set_default_aspect(cdouble aspect = 4.0 / 3.0); //set before default projection
	DLL_EXPORT void DLL_CALL set_default_projection(cdouble width = -1.0, cdouble height = -1.0); //set after opening window
	#endif
	DLL_EXPORT void DLL_CALL set_default_projection(cdouble x1, cdouble y1, cdouble x2, cdouble y2); //set after opening window
	DLL_EXPORT void DLL_CALL set_projection(cdouble width, cdouble height);
	DLL_EXPORT void DLL_CALL set_projection(cdouble x1, cdouble y1, cdouble x2, cdouble y2);
	DLL_EXPORT void DLL_CALL set_fov(cdouble fov, cdouble aspect = 1.0, cdouble znear = 0.1, cdouble zfar = 10.0);
	DLL_EXPORT void DLL_CALL look_at(cdouble eyeX, cdouble eyeY, cdouble eyeZ, cdouble centerX, cdouble centerY, cdouble centerZ, cdouble upX, cdouble upY, cdouble upZ);
	DLL_EXPORT void DLL_CALL draw_box(cfloat x, cfloat y, cfloat width, cfloat height);
	DLL_EXPORT void DLL_CALL draw_rotated_box(cfloat x, cfloat y, cfloat width, cfloat height, cfloat rotation);
	DLL_EXPORT void DLL_CALL draw_part_box(cfloat x, cfloat y, cfloat width, cfloat height,
		cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2);
	DLL_EXPORT void DLL_CALL draw_image(const texture &_texture, cfloat x, cfloat y, cfloat width, cfloat height);
	DLL_EXPORT void DLL_CALL draw_image(const texture *_texture, cfloat x, cfloat y, cfloat width, cfloat height);
	DLL_EXPORT void DLL_CALL draw_rotated_image(const texture &_texture, cfloat x, cfloat y, cfloat width, cfloat height, cfloat rotation);
	DLL_EXPORT void DLL_CALL draw_rotated_image(const texture *_texture, cfloat x, cfloat y, cfloat width, cfloat height, cfloat rotation);
	DLL_EXPORT void DLL_CALL draw_part_image(const texture &_texture, cfloat x, cfloat y, cfloat width, cfloat height,
		cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2);
	DLL_EXPORT void DLL_CALL draw_part_image(const texture *_texture, cfloat x, cfloat y, cfloat width, cfloat height,
		cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2);
}

#endif
