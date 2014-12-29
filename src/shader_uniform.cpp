/** shader_uniform.cpp **/

#include "shader.hpp"
#include "log_ios.hpp"

namespace strf {

	shader::shader_uniform::shader_uniform(const std::vector<GLint> &_uniforms, const std::vector<uchar> &_uniform_types):
		uniforms(_uniforms),
		uniform_types(_uniform_types) {
	}

	void shader::shader_uniform::reset() {
		i = 0;
		j = 0;
	}

	//This same shit is pretty musch copy pasted three times here
	shader::shader_uniform &shader::shader_uniform::operator<<(cfloat value) {
		if(i == uniforms.size()) {
			if(strf_logging) std::cout << "STRF Warning: Too many uniform values given for a shader" << std::endl;
		}
		else {
			//FLOAT
			if(uniform_types.at(i) == STRF_FLOAT1) {
				glUniform1f(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_FLOAT2) {
				if(j == 1) {
					glUniform2f(uniforms.at(i), floats[0], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_FLOAT3) {
				if(j == 2) {
					glUniform3f(uniforms.at(i), floats[0], floats[1], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_FLOAT4) {
				if(j == 3) {
					glUniform4f(uniforms.at(i), floats[0], floats[1], floats[2], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			//INT
			else if(uniform_types.at(i) == STRF_INT1) {
				glUniform1i(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_INT2) {
				if(j == 1) {
					glUniform2i(uniforms.at(i), ints[0], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_INT3) {
				if(j == 2) {
					glUniform3i(uniforms.at(i), ints[0], ints[1], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_INT4) {
				if(j == 3) {
					glUniform4i(uniforms.at(i), ints[0], ints[1], ints[2], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			//UNSIGNED INT
			else if(uniform_types.at(i) == STRF_UINT1) {
				glUniform1ui(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_UINT2) {
				if(j == 1) {
					glUniform2ui(uniforms.at(i), uints[0], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_UINT3) {
				if(j == 2) {
					glUniform3ui(uniforms.at(i), uints[0], uints[1], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_UINT4) {
				if(j == 3) {
					glUniform4ui(uniforms.at(i), uints[0], uints[1], uints[2], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			if(!j) i++;
		}
		return *this;
	}

	shader::shader_uniform &shader::shader_uniform::operator<<(cint value) {
		if(i == uniforms.size()) {
			if(strf_logging) std::cout << "STRF Warning: Too many uniform values given for a shader" << std::endl;
		}
		else {
			//FLOAT
			if(uniform_types.at(i) == STRF_FLOAT1) {
				glUniform1f(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_FLOAT2) {
				if(j == 1) {
					glUniform2f(uniforms.at(i), floats[0], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_FLOAT3) {
				if(j == 2) {
					glUniform3f(uniforms.at(i), floats[0], floats[1], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_FLOAT4) {
				if(j == 3) {
					glUniform4f(uniforms.at(i), floats[0], floats[1], floats[2], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			//INT
			else if(uniform_types.at(i) == STRF_INT1) {
				glUniform1i(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_INT2) {
				if(j == 1) {
					glUniform2i(uniforms.at(i), ints[0], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_INT3) {
				if(j == 2) {
					glUniform3i(uniforms.at(i), ints[0], ints[1], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_INT4) {
				if(j == 3) {
					glUniform4i(uniforms.at(i), ints[0], ints[1], ints[2], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			//UNSIGNED INT
			else if(uniform_types.at(i) == STRF_UINT1) {
				glUniform1ui(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_UINT2) {
				if(j == 1) {
					glUniform2ui(uniforms.at(i), uints[0], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_UINT3) {
				if(j == 2) {
					glUniform3ui(uniforms.at(i), uints[0], uints[1], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_UINT4) {
				if(j == 3) {
					glUniform4ui(uniforms.at(i), uints[0], uints[1], uints[2], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			if(!j) i++;
		}
		return *this;
	}

	shader::shader_uniform &shader::shader_uniform::operator<<(cuint value) {
		if(i == uniforms.size()) {
			if(strf_logging) std::cout << "STRF Warning: Too many uniform values given for a shader" << std::endl;
		}
		else {
			//FLOAT
			if(uniform_types.at(i) == STRF_FLOAT1) {
				glUniform1f(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_FLOAT2) {
				if(j == 1) {
					glUniform2f(uniforms.at(i), floats[0], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_FLOAT3) {
				if(j == 2) {
					glUniform3f(uniforms.at(i), floats[0], floats[1], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_FLOAT4) {
				if(j == 3) {
					glUniform4f(uniforms.at(i), floats[0], floats[1], floats[2], value);
					j = 0;
				}
				else {
					floats[j] = value;
					j++;
				}
			}
			//INT
			else if(uniform_types.at(i) == STRF_INT1) {
				glUniform1i(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_INT2) {
				if(j == 1) {
					glUniform2i(uniforms.at(i), ints[0], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_INT3) {
				if(j == 2) {
					glUniform3i(uniforms.at(i), ints[0], ints[1], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_INT4) {
				if(j == 3) {
					glUniform4i(uniforms.at(i), ints[0], ints[1], ints[2], value);
					j = 0;
				}
				else {
					ints[j] = value;
					j++;
				}
			}
			//UNSIGNED INT
			else if(uniform_types.at(i) == STRF_UINT1) {
				glUniform1ui(uniforms.at(i), value);
			}
			else if(uniform_types.at(i) == STRF_UINT2) {
				if(j == 1) {
					glUniform2ui(uniforms.at(i), uints[0], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_UINT3) {
				if(j == 2) {
					glUniform3ui(uniforms.at(i), uints[0], uints[1], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			else if(uniform_types.at(i) == STRF_UINT4) {
				if(j == 3) {
					glUniform4ui(uniforms.at(i), uints[0], uints[1], uints[2], value);
					j = 0;
				}
				else {
					uints[j] = value;
					j++;
				}
			}
			if(!j) i++;
		}
		return *this;
	}

}
