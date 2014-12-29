/** framebuffer.hpp **/

#ifndef STRF_FRAMEBUFFER_HPP
#define STRF_FRAMEBUFFER_HPP

#include <strf/global.hpp>

/*

	save_buffer:
		glViewport(0, 0, resolution->first, resolution->second)

	draw_buffer:
		set_projection(1, 1)
		glViewport(0, 0, resolution->first, resolution->second)

*/

namespace strf {
	#ifndef STRF_INIT_HPP
	#ifndef STRF_FBO_HPP
	DLL_EXPORT void DLL_CALL force_framebuffer_dimensions(cushort width = 0, cushort height = 0); //set after opening window and quit() resets
	#endif
	#endif
	DLL_EXPORT void DLL_CALL save_buffer(cuchar id);
	DLL_EXPORT void DLL_CALL draw_buffer(cuchar id, cbool clear = false);
	DLL_EXPORT void DLL_CALL redraw_framebuffer(cbool clear = false);
}

#endif
