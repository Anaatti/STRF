/** init.hpp **/

#ifndef STRF_INIT_HPP
#define STRF_INIT_HPP

#include <strf/global.hpp>

#define STRF_INIT_GLEW 01
#define STRF_INIT_FRAMEBUFFER 02
#define STRF_INIT_SCREENSHOT 04
#define STRF_INIT_FONT 010
#define STRF_INIT_SHADER 020
#define STRF_INIT_ALL (STRF_INIT_GLEW | STRF_INIT_FRAMEBUFFER | STRF_INIT_SCREENSHOT | STRF_INIT_FONT | STRF_INIT_SHADER)
#define STRF_INIT_DEFAULT STRF_INIT_ALL

#define STRF_MIPMAP_ALL 0
#define STRF_MIPMAP_SOME 1
#define STRF_MIPMAP_NONE 2

namespace strf {
	DLL_EXPORT void DLL_CALL init_only(cuchar init);
	DLL_EXPORT void DLL_CALL init_add(cuchar init);
	DLL_EXPORT void DLL_CALL init_remove(cuchar init);
	DLL_EXPORT void DLL_CALL set_resizable(cbool _resizable = false); //set before opening window
	DLL_EXPORT void DLL_CALL set_antialiasing(cuchar _antialiasing = 4); //set before opening window
	DLL_EXPORT void DLL_CALL set_depth_bits(cuchar _depth_bits = 0); //set before opening window
	DLL_EXPORT void DLL_CALL set_stencil_bits(cuchar _stencil_bits = 0); //set before opening window
	DLL_EXPORT void DLL_CALL set_caption(cchar *_caption = "STRF program"); //set at will and quit() resets
	DLL_EXPORT void DLL_CALL set_vsync(cbool _vsync = true); //set at will
	DLL_EXPORT void DLL_CALL show_mouse(cbool _mouse = true); //set at will
	#ifndef STRF_DRAW_HPP
	DLL_EXPORT void DLL_CALL set_default_aspect(cdouble aspect = 4.0 / 3.0); //set before default projection
	DLL_EXPORT void DLL_CALL set_default_projection(cdouble width = -1.0, cdouble height = -1.0); //set after opening window
	#endif
	DLL_EXPORT void DLL_CALL set_default_projection(cdouble x1, cdouble y1, cdouble x2, cdouble y2); //set after opening window
	#ifndef STRF_FRAMEBUFFER_HPP
	#ifndef STRF_FBO_HPP
	DLL_EXPORT void DLL_CALL force_framebuffer_dimensions(cushort width = 0, cushort height = 0); //set after opening window and quit() resets
	#endif
	#endif
	DLL_EXPORT void DLL_CALL set_texture_wrap(cint wrap /* = GL_REPEAT*/); //set before opening window to affect font
	DLL_EXPORT void DLL_CALL set_texture_filter(cint filter /* = GL_LINEAR*/); //set before opening window to affect font
	DLL_EXPORT void DLL_CALL set_texture_mipmap(cuchar mipmap = STRF_MIPMAP_SOME); //set before opening window to affect font
	DLL_EXPORT void DLL_CALL set_fps_draw(cbool value = false); //set at will
	#ifndef STRF_FPS_HPP
	DLL_EXPORT void DLL_CALL set_fps_draw_size(cfloat value = 40.0); //set at will
	#endif
	#ifndef STRF_TEXT_HPP
	DLL_EXPORT void DLL_CALL set_text_scale(cfloat scale = 1.0); //set at will
	DLL_EXPORT void DLL_CALL set_text_spacing(cfloat spacing = 1.0); //set at will
	#endif
	DLL_EXPORT void DLL_CALL set_logging(cbool value = true); //set before initializing to affect init log
	DLL_EXPORT void DLL_CALL set_shader_logging(cbool value = true); //set at will
	DLL_EXPORT void DLL_CALL set_log_file(cchar *filename = 0); //set before initializing to affect init log and quit() resets
	DLL_EXPORT void DLL_CALL set_error_log_file(cchar *filename = 0); //set before initializing to affect init log and quit() resets
	DLL_EXPORT void DLL_CALL set_shader_log_file(cchar *filename = 0); //set before initializing to affect init log and quit() resets
	DLL_EXPORT cchar DLL_CALL *get_error_string();
	DLL_EXPORT bool DLL_CALL init();
	DLL_EXPORT void DLL_CALL close_window();
	DLL_EXPORT bool DLL_CALL open_window(cushort width, cushort height, cbool fullscreen = false);
	DLL_EXPORT void DLL_CALL quit();
}

#endif
