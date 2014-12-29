/** texture.cpp **/

#include "texture.hpp"
#include "load_texture.hpp"
#include "math.hpp"
#include "log.hpp"
#include <cstring>

#define STRF_MIPMAP_ALL 0
#define STRF_MIPMAP_SOME 1
#define STRF_MIPMAP_NONE 2

namespace strf {

	bool anisotrophic_filtering;
	float max_anisotrophy;

	void set_anisotrophic_filtering() {
		if(glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
			anisotrophic_filtering = true;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotrophy);
			if(strf_logging) log << "STRF: Got " << max_anisotrophy << "x anisotrophic filtering" << endl;
		}
		else {
			anisotrophic_filtering = false;
			if(strf_logging) log << "STRF: Didn't get anisotrophic filtering" << endl;
		}
	}

	GLint texture_wrap = GL_REPEAT;
	GLint texture_filter = GL_LINEAR;
	uchar texture_mipmap = STRF_MIPMAP_SOME;

	DLL_EXPORT void DLL_CALL set_texture_wrap(cint wrap) {
		texture_wrap = wrap;
	}

	DLL_EXPORT void DLL_CALL set_texture_filter(cint filter) {
		texture_filter = filter;
	}

	DLL_EXPORT void DLL_CALL set_texture_mipmap(cuchar mipmap) {
		texture_mipmap = mipmap;
	}

	texture::texture(cbool quality):
		path(0),
		pixels(0) {
		generate_texture(quality, false, 3, 3);
	}

	texture::texture(cchar *_path, cbool quality, cbool _mipmap):
		path(new char[strlen(_path) + 1]),
		pixels(0) {
		memcpy(path, _path, strlen(_path) + 1);
		const bitmap *_bitmap = load_texture(path);
		if(_bitmap) {
			generate_texture(quality, _mipmap, _bitmap->width, _bitmap->height);
			if(mipmap) gluBuild2DMipmaps(GL_TEXTURE_2D, _bitmap->alpha ? 4 : 3, _bitmap->width, _bitmap->height, _bitmap->alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _bitmap->data);
			else glTexImage2D(GL_TEXTURE_2D, 0, _bitmap->alpha ? 4 : 3, _bitmap->width, _bitmap->height, 0, _bitmap->alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _bitmap->data);
			delete _bitmap;
		}
	}

	texture::texture(const bitmap &_bitmap, cbool quality, cbool _mipmap, cbool save_bitmap):
		path(0),
		pixels(save_bitmap ? new uchar[_bitmap.width * _bitmap.height * (_bitmap.alpha ? 4 : 3)] : 0) {
		if(save_bitmap) memcpy(pixels, _bitmap.data, _bitmap.width * _bitmap.height * (_bitmap.alpha ? 4 : 3));
		generate_texture(quality, _mipmap, _bitmap.width, _bitmap.height);
		if(mipmap) gluBuild2DMipmaps(GL_TEXTURE_2D, _bitmap.alpha ? 4 : 3, _bitmap.width, _bitmap.height, _bitmap.alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _bitmap.data);
		else glTexImage2D(GL_TEXTURE_2D, 0, _bitmap.alpha ? 4 : 3, _bitmap.width, _bitmap.height, 0, _bitmap.alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _bitmap.data);
	}	//COPY
		texture::texture(const bitmap *_bitmap, cbool quality, cbool _mipmap, cbool save_bitmap):
			path(0),
			pixels(save_bitmap ? new uchar[_bitmap->width * _bitmap->height * (_bitmap->alpha ? 4 : 3)] : 0) {
			if(save_bitmap) memcpy(pixels, _bitmap->data, _bitmap->width * _bitmap->height * (_bitmap->alpha ? 4 : 3));
			generate_texture(quality, _mipmap, _bitmap->width, _bitmap->height);
			if(mipmap) gluBuild2DMipmaps(GL_TEXTURE_2D, _bitmap->alpha ? 4 : 3, _bitmap->width, _bitmap->height, _bitmap->alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _bitmap->data);
			else glTexImage2D(GL_TEXTURE_2D, 0, _bitmap->alpha ? 4 : 3, _bitmap->width, _bitmap->height, 0, _bitmap->alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _bitmap->data);
		}

	texture::~texture() {
		delete [] path;
		delete [] pixels;
		glDeleteTextures(1, &tex);
	}

	void texture::generate_texture(cbool quality, cbool _mipmap, cushort width, cushort height) {
		mipmap = _mipmap && (texture_mipmap == STRF_MIPMAP_ALL || (texture_mipmap == STRF_MIPMAP_SOME && is_power_of_two(width) && is_power_of_two(height)));
		filter = quality ? texture_filter : GL_NEAREST;
		if(mipmap) filter = filter == GL_LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		if(anisotrophic_filtering && mipmap) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotrophy);
	}

	void texture::use() const {
		glBindTexture(GL_TEXTURE_2D, tex);
	}

	void texture::operator()() const {
		glBindTexture(GL_TEXTURE_2D, tex);
	}

	GLuint texture::get_texture() const {
		return tex;
	}

}
