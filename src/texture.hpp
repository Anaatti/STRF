/** texture.hpp **/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "global.hpp"
#include "bitmap.hpp"
#include <GL/glew.h>

namespace strf {

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
