/** shader.cpp **/

#include "shader.hpp"
#include "init.hpp"
#include "log.hpp"
#include <fstream>
#include <cstring>
#include <cstdarg>

namespace strf {

	DLL_EXPORT shader *color_shader;
	DLL_EXPORT shader *basic_shader;

	bool shaders_initialized = false;

	bool log_shaders = true;

	DLL_EXPORT void DLL_CALL set_shader_logging(cbool value) {
		log_shaders = value;
	}

	enum {
		PROGRAM, SHADER
	};

	void print_shader_log(const GLuint obj, cuchar type) {
		if(log_shaders && strf_logging) {
			int log_length;
			if(type == SHADER) glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &log_length);
			else glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &log_length);
			if(log_length > 0) {
				int chars_written;
				char *_log = new char[log_length];
				if(type == SHADER) glGetShaderInfoLog(obj, log_length, &chars_written, _log);
				else glGetProgramInfoLog(obj, log_length, &chars_written, _log);
				if(type == PROGRAM) log_shader << "STRF: Shader program info log:\n" << _log << endl;
				else log_shader << _log << endl;
				delete [] _log;
			}
		}
	}

	GLuint load_shader(cchar *path, const GLenum type) {
		try {
			std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
			cuint size = file.tellg();
			if(!file.good() || size <= 2) {
				file.close();
				if(strf_logging) log_error << "STRF Error: Couldn't load a shader from " << path << "!" << endl;
				return 0;
			}
			file.seekg(0, std::ios::beg);
			char *source = new char[size];
			file.read(source, size);
			file.close();

			//Create shader
			const GLuint shader = glCreateShader(type);
			cchar *_source = source;
			const GLint _size = size;
			glShaderSource(shader, 1, &_source, &_size);
			delete [] source;
			glCompileShader(shader);
			if(log_shaders && strf_logging) log_shader << "STRF: Log for " << path << ":" << endl;
			print_shader_log(shader, SHADER);
			return shader;
		}
		catch(const std::exception &e) {
			if(strf_logging) {
				log_error << "STRF Error: Standard exception while loading the shader: " << path << endl;
				print_exception(e);
			}
			return 0;
		}
	}

	GLuint load_shader_source(cchar *source, const GLenum type) {
		const GLint size = strlen(source);
		const GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, &size);
		glCompileShader(shader);
		if(log_shaders && strf_logging) log_shader << "STRF: Log for a " << (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader:" << endl;
		print_shader_log(shader, SHADER);
		return shader;
	}

	void load_strf_shaders() {
		if(glew_initialized && (init_choise & STRF_INIT_SHADER)) {
			color_shader = new shader(true);
			basic_shader = new shader(false);
			shaders_initialized = true;
		}
	}

	void delete_strf_shaders() {
		if(shaders_initialized) {
			delete color_shader;
			delete basic_shader;
			shaders_initialized = false;
		}
	}

	shader::shader():
		program(glCreateProgram()),
		uniform_assign(uniforms, uniform_types) {
	}

	shader::shader(cbool strf_shader):
		program(glCreateProgram()),
		uniform_assign(uniforms, uniform_types) {
		if(strf_shader) { //color shader
			vertex_shaders.push_back(load_shader_source(
				"#version 110\nvoid main(){gl_FrontColor=gl_Color;gl_Position=ftransform();}",
				GL_VERTEX_SHADER));
			fragment_shaders.push_back(load_shader_source(
				"#version 110\nvoid main(){gl_FragColor=gl_Color;}",
				GL_FRAGMENT_SHADER));
		}
		else { //basic shader
			vertex_shaders.push_back(load_shader_source(
				"#version 110\nvoid main(){gl_TexCoord[0]=gl_MultiTexCoord0;gl_FrontColor=gl_Color;gl_Position=ftransform();}",
				GL_VERTEX_SHADER));
			fragment_shaders.push_back(load_shader_source(
				"#version 110\nuniform sampler2D texture1;void main(){gl_FragColor=texture2D(texture1,gl_TexCoord[0].st)*gl_Color;}",
				GL_FRAGMENT_SHADER));
		}
		glAttachShader(program, vertex_shaders.back());
		glAttachShader(program, fragment_shaders.back());
		glLinkProgram(program);
		glUseProgram(program);
		print_shader_log(program, PROGRAM);
	}

	shader::shader(cchar *vprog, cchar *fprog, cbool random):
		program(glCreateProgram()),
		uniform_assign(uniforms, uniform_types) {
		if(random) add_random_shader();
		add_fragment_shader(fprog);
		add_vertex_shader(vprog);
	}

	shader::~shader() {
		for(std::vector<GLuint>::const_iterator i=vertex_shaders.begin();i!=vertex_shaders.end();i++) {
			glDetachShader(program, *i);
			glDeleteShader(*i);
		}
		for(std::vector<GLuint>::const_iterator i=fragment_shaders.begin();i!=fragment_shaders.end();i++) {
			glDetachShader(program, *i);
			glDeleteShader(*i);
		}
		glDeleteProgram(program);
	}

	void shader::add_random_shader() {
		fragment_shaders.push_back(load_shader_source(
			"#version 110\nfloat random(in float seed){return fract((sin(7.0*seed)+cos(13.0*seed)+fract(seed))*752.37);}",
			GL_FRAGMENT_SHADER));
		glAttachShader(program, fragment_shaders.back());
		if(!vertex_shaders.empty() && !fragment_shaders.empty()) {
			glLinkProgram(program);
			glUseProgram(program);
			print_shader_log(program, PROGRAM);
		}
	}

	void shader::add_vertex_shader(cchar *vprog) {
		vertex_shaders.push_back(load_shader(vprog, GL_VERTEX_SHADER));
		glAttachShader(program, vertex_shaders.back());
		if(!vertex_shaders.empty() && !fragment_shaders.empty()) {
			glLinkProgram(program);
			glUseProgram(program);
			print_shader_log(program, PROGRAM);
		}
	}

	void shader::add_fragment_shader(cchar *fprog) {
		fragment_shaders.push_back(load_shader(fprog, GL_FRAGMENT_SHADER));
		glAttachShader(program, fragment_shaders.back());
		if(!vertex_shaders.empty() && !fragment_shaders.empty()) {
			glLinkProgram(program);
			glUseProgram(program);
			print_shader_log(program, PROGRAM);
		}
	}

	void shader::add_uniform(cuchar type, cchar *name) {
		uniform_types.push_back(type);
		uniforms.push_back(glGetUniformLocation(program, name));
	}

	void shader::use(cuchar nothing, ...) const {
		glUseProgram(program);
		va_list args;
		va_start(args, nothing);
		for(uchar i=0;i<uniforms.size();i++) {
			//FLOAT
			if(uniform_types.at(i) == STRF_FLOAT1) {
				glUniform1f(uniforms.at(i), va_arg(args, double));
			}
			else if(uniform_types.at(i) == STRF_FLOAT2) {
				cfloat a = va_arg(args, double);
				glUniform2f(uniforms.at(i), a, va_arg(args, double));
			}
			else if(uniform_types.at(i) == STRF_FLOAT3) {
				cfloat a = va_arg(args, double);
				cfloat b = va_arg(args, double);
				glUniform3f(uniforms.at(i), a, b, va_arg(args, double));
			}
			else if(uniform_types.at(i) == STRF_FLOAT4) {
				cfloat a = va_arg(args, double);
				cfloat b = va_arg(args, double);
				cfloat c = va_arg(args, double);
				glUniform4f(uniforms.at(i), a, b, c, va_arg(args, double));
			}
			//INT
			else if(uniform_types.at(i) == STRF_INT1) {
				glUniform1i(uniforms.at(i), va_arg(args, int));
			}
			else if(uniform_types.at(i) == STRF_INT2) {
				cint a = va_arg(args, int);
				glUniform2i(uniforms.at(i), a, va_arg(args, int));
			}
			else if(uniform_types.at(i) == STRF_INT3) {
				cint a = va_arg(args, int);
				cint b = va_arg(args, int);
				glUniform3i(uniforms.at(i), a, b, va_arg(args, int));
			}
			else if(uniform_types.at(i) == STRF_INT4) {
				cint a = va_arg(args, int);
				cint b = va_arg(args, int);
				cint c = va_arg(args, int);
				glUniform4i(uniforms.at(i), a, b, c, va_arg(args, int));
			}
			//UNSIGNED INT
			else if(uniform_types.at(i) == STRF_UINT1) {
				glUniform1ui(uniforms.at(i), va_arg(args, int));
			}
			else if(uniform_types.at(i) == STRF_UINT2) {
				cuint a = va_arg(args, int);
				glUniform2ui(uniforms.at(i), a, va_arg(args, int));
			}
			else if(uniform_types.at(i) == STRF_UINT3) {
				cuint a = va_arg(args, int);
				cuint b = va_arg(args, int);
				glUniform3ui(uniforms.at(i), a, b, va_arg(args, int));
			}
			else if(uniform_types.at(i) == STRF_UINT4) {
				cuint a = va_arg(args, int);
				cuint b = va_arg(args, int);
				cuint c = va_arg(args, int);
				glUniform4ui(uniforms.at(i), a, b, c, va_arg(args, int));
			}
		}
		va_end(args);
	}

	void shader::use() const {
		glUseProgram(program);
	}

	void shader::operator()() const {
		glUseProgram(program);
	}

	shader::shader_uniform &shader::operator<<(cfloat value) {
		glUseProgram(program);
		uniform_assign.reset();
		return uniform_assign << value;
	}

	shader::shader_uniform &shader::operator<<(cint value) {
		glUseProgram(program);
		uniform_assign.reset();
		return uniform_assign << value;
	}

	shader::shader_uniform &shader::operator<<(cuint value) {
		glUseProgram(program);
		uniform_assign.reset();
		return uniform_assign << value;
	}

}
