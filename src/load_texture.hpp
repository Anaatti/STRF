/** load_texture.hpp **/

#ifndef LOAD_TEXTURE_HPP
#define LOAD_TEXTURE_HPP

#include "global.hpp"
#include "bitmap.hpp"

namespace strf {

	DLL_EXPORT bitmap* DLL_CALL load_texture(cchar *path);
	DLL_EXPORT bitmap* DLL_CALL parse_bmp(cuchar *data);
	DLL_EXPORT bitmap* DLL_CALL parse_png(cuchar *data, cuint size);

}

#endif
