/** init.hpp **/

#ifndef INIT_HPP
#define INIT_HPP

#include "global.hpp"
#include <utility>

#define STRF_INIT_GLEW 01
#define STRF_INIT_FRAMEBUFFER 02
#define STRF_INIT_SCREENSHOT 04
#define STRF_INIT_FONT 010
#define STRF_INIT_SHADER 020
#define STRF_INIT_ALL (STRF_INIT_GLEW | STRF_INIT_FRAMEBUFFER | STRF_INIT_SCREENSHOT | STRF_INIT_FONT | STRF_INIT_SHADER)
#define STRF_INIT_DEFAULT STRF_INIT_ALL

namespace strf {
	extern DLL_EXPORT std::pair<uint, uint> *resolution;
	extern std::pair<uint, uint> *shader_resolution;
	extern uchar init_choise;
	extern bool glew_initialized;
	extern bool resizable;
}

#endif
