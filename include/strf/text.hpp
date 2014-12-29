/** text.hpp **/

#ifndef STRF_TEXT_HPP
#define STRF_TEXT_HPP

#include <strf/texture.hpp>

namespace strf {
	#ifndef STRF_INIT_HPP
	DLL_EXPORT void DLL_CALL set_text_scale(cfloat scale = 1.0);
	DLL_EXPORT void DLL_CALL set_text_spacing(cfloat spacing = 1.0);
	#endif
	DLL_EXPORT void DLL_CALL draw_text(cchar *text, cfloat x, cfloat y, cfloat size, cuchar align);
	DLL_EXPORT void DLL_CALL draw_char(cchar c, cfloat x, cfloat y, cfloat size, cuchar align);
	DLL_EXPORT void DLL_CALL draw_vertical_text(cchar *text, cfloat x, cfloat y, cfloat size, cuchar align);
	DLL_EXPORT void DLL_CALL draw_int(cint value, cfloat x, cfloat y, cfloat size, cuchar align);
	DLL_EXPORT void DLL_CALL draw_float(cfloat value, cuchar precision, cfloat x, cfloat y, cfloat size, cuchar align);

	extern DLL_EXPORT texture *font[256];
}

#endif
