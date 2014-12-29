/** fbo.cpp **/

#include "init.hpp"
#include "math.hpp"
#include "fbo.hpp"

namespace strf {

	DLL_EXPORT void DLL_CALL set_projection(cdouble width, cdouble height);
	DLL_EXPORT void DLL_CALL draw_part_image(const texture &_texture, cfloat x, cfloat y, cfloat width, cfloat height,
		cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2);

	DLL_EXPORT void DLL_CALL use_fbo_0() {
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}

	fbo::fbo(cuint width, cuint height, cbool quality):
		tex(quality) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width ? width : resolution->first, height ? height : resolution->second, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
		glGenFramebuffersEXT(1, &framebuffer);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex.get_texture(), 0);
	}

	fbo::~fbo() {
		glDeleteFramebuffersEXT(1, &framebuffer);
	}

	void fbo::use() const {
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	}

	void fbo::operator()() const {
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	}

	void fbo::use_texture() const {
		tex();
	}

	const texture &fbo::get_texture() const {
		return tex;
	}

	void fbo::draw(cbool clear) const {
		if(clear) glClear(GL_COLOR_BUFFER_BIT);
		set_projection(1, 1);
		glViewport(0, 0, strfmin(shader_resolution->first, resolution->first), strfmin(shader_resolution->second, resolution->second));
		draw_part_image(tex, 0, 0, 1, 1, 0, strfmin((float)resolution->first / (float)shader_resolution->first, 1.0), 0, strfmin((float)resolution->second / (float)shader_resolution->second, 1.0));
		glViewport(0, 0, resolution->first, resolution->second);
	}

}
