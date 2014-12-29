/** shader.hpp **/

#ifndef STRF_SHADER_HPP
#define STRF_SHADER_HPP

#include <strf/global.hpp>
#include <vector>
#include <GL/gl.h>

#define STRF_FLOAT 0
#define STRF_FLOAT1 0
#define STRF_FLOAT2 1
#define STRF_FLOAT3 2
#define STRF_FLOAT4 3
#define STRF_VEC1 0
#define STRF_VEC2 1
#define STRF_VEC3 2
#define STRF_VEC4 3
#define STRF_INT 4
#define STRF_INT1 4
#define STRF_INT2 5
#define STRF_INT3 6
#define STRF_INT4 7
#define STRF_UINT 8
#define STRF_UINT1 8
#define STRF_UINT2 9
#define STRF_UINT3 10
#define STRF_UINT4 11

namespace strf {

	class DLL_EXPORT shader {
		public:
			class DLL_EXPORT shader_uniform {
				private:
					const std::vector<GLint> &uniforms;
					const std::vector<uchar> &uniform_types;
					uchar i, j;
					float floats[3];
					int ints[3];
					uint uints[3];
				public:
					shader_uniform(const std::vector<GLint> &_uniforms, const std::vector<uchar> &_uniform_types);
					void reset();
					shader_uniform &operator<<(cfloat value);
					shader_uniform &operator<<(cint value);
					shader_uniform &operator<<(cuint value);
			};

		private:
			shader(const shader &shd); //Copy constructor
			shader &operator=(const shader &shd); //Assign operator
			const GLuint program;
			std::vector<GLuint> vertex_shaders;
			std::vector<GLuint> fragment_shaders;
			std::vector<GLint> uniforms;
			std::vector<uchar> uniform_types;
			shader_uniform uniform_assign;

		public:
			shader();
			shader(cbool strf_shader);
			shader(cchar *vprog, cchar *fprog, cbool random = false);
			~shader();
			void add_random_shader();
			void add_vertex_shader(cchar *vprog);
			void add_fragment_shader(cchar *fprog);
			void add_uniform(cuchar type, cchar *name);
			void use(cuchar nothing, ...) const;
			void use() const;
			void operator()() const;
			shader_uniform &operator<<(cfloat value);
			shader_uniform &operator<<(cint value);
			shader_uniform &operator<<(cuint value);
	};

	extern DLL_EXPORT shader *color_shader;
	extern DLL_EXPORT shader *basic_shader;

}

#endif
