/** fbo.hpp **/

#ifndef STRF_FBO_HPP
#define STRF_FBO_HPP

#include <strf/texture.hpp>
#include <GL/gl.h>

/*

	draw:
		set_projection(1, 1)
		glViewport(0, 0, resolution->first, resolution->second)

*/

namespace strf {

	#ifndef STRF_INIT_HPP
	#ifndef STRF_FRAMEBUFFER_HPP
	DLL_EXPORT void DLL_CALL force_framebuffer_dimensions(cushort width = 0, cushort height = 0); //set after opening window and quit() resets
	#endif
	#endif
	DLL_EXPORT void DLL_CALL use_fbo_0();

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
