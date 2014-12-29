/** fbo.hpp **/

#ifndef FBO_HPP
#define FBO_HPP

#include "global.hpp"
#include "texture.hpp"
#include <GL/glew.h>

namespace strf {

	class DLL_EXPORT fbo {
		private:
			fbo(const fbo &_fbo); //Copy constructor
			fbo &operator=(const fbo &_fbo); //Assign operator
			texture tex;
			GLuint framebuffer;

		public:
			fbo(cuint width = 0, cuint height = 0, cbool quality = true);
			~fbo();
			void use() const;
			void operator()() const;
			void use_texture() const;
			const texture &get_texture() const;
			void draw(cbool clear = false) const;
	};

}

#endif
