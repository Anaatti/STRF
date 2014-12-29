/** texture.hpp **/

#ifndef STRF_TEXTURE_HPP
#define STRF_TEXTURE_HPP

#include <strf/bitmap.hpp>
#include <GL/gl.h>

namespace strf {

	DLL_EXPORT bitmap* DLL_CALL load_texture(cchar *path);
	DLL_EXPORT bitmap* DLL_CALL parse_bmp(cuchar *data);
	DLL_EXPORT bitmap* DLL_CALL parse_png(cuchar *data, cuint size);

	class DLL_EXPORT texture {
		private:
			texture(const texture &tex); //Copy constructor
			texture &operator=(const texture &tex); //Assign operator
			void generate_texture(cbool quality, cbool _mipmap, cushort width, cushort height);
			GLuint tex;
			char *path;
			uchar *pixels;
			GLint filter;
			bool mipmap;

		public:
			texture(cbool quality = true);
			texture(cchar *_path, cbool quality = true, cbool _mipmap = true);
			texture(const bitmap &_bitmap, cbool quality = true, cbool _mipmap = true, cbool save_bitmap = false);
			texture(const bitmap *_bitmap, cbool quality = true, cbool _mipmap = true, cbool save_bitmap = false);
			~texture();
			void use() const;
			void operator()() const;
			GLuint get_texture() const;
	};

}

#endif
