/** log.cpp **/

#include "log.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#ifdef _WIN32
	#include <windows.h>
#endif

namespace strf {

	bool strf_logging = true;

	DLL_EXPORT void DLL_CALL set_logging(cbool value) {
		strf_logging = value;
	}

	DLL_EXPORT endl_s endl;
	DLL_EXPORT log_c log;
	DLL_EXPORT log_error_c log_error;
	log_shader_c log_shader;

	std::string *log_filename = 0;
	std::string *error_log_filename = 0;
	std::string *shader_log_filename = 0;

	std::ofstream *log_file = 0;
	std::ofstream *error_log_file = 0;
	std::ofstream *shader_log_file = 0;

	inline void close_log_file() {
		if(log_file) {
			log_file->close();
			delete log_file;
			log_file = 0;
		}
	}

	inline void close_error_log_file() {
		if(error_log_file) {
			error_log_file->close();
			delete error_log_file;
			error_log_file = 0;
		}
	}

	inline void close_shader_log_file() {
		if(shader_log_file) {
			shader_log_file->close();
			delete shader_log_file;
			shader_log_file = 0;
		}
	}

	DLL_EXPORT void DLL_CALL set_log_file(cchar *filename) {
		close_log_file();
		if(filename) {
			if(!log_filename) log_filename = new std::string(filename);
			else log_filename->assign(filename);
		}
		else {
			delete log_filename;
			log_filename = 0;
		}
	}

	DLL_EXPORT void DLL_CALL set_error_log_file(cchar *filename) {
		close_error_log_file();
		if(filename) {
			if(!error_log_filename) error_log_filename = new std::string(filename);
			else error_log_filename->assign(filename);
		}
		else {
			delete error_log_filename;
			error_log_filename = 0;
		}
	}

	DLL_EXPORT void DLL_CALL set_shader_log_file(cchar *filename) {
		close_shader_log_file();
		if(filename) {
			if(!shader_log_filename) shader_log_filename = new std::string(filename);
			else shader_log_filename->assign(filename);
		}
		else {
			delete shader_log_filename;
			shader_log_filename = 0;
		}
	}

	inline std::ofstream *get_log_file() {
		if(log_filename && !log_file) {
			log_file = new std::ofstream(log_filename->c_str());
			if(!log_file->good()) close_log_file();
			else {
				(*log_file) << "Created at: ";
				const time_t _time = time(NULL);
				(*log_file) << asctime(localtime(&_time));
			}
		}
		return log_file;
	}

	inline std::ofstream *get_error_log_file() {
		if(error_log_filename) {
			if(!error_log_file) {
				error_log_file = new std::ofstream(error_log_filename->c_str());
				if(!error_log_file->good()) close_error_log_file();
				else {
					(*error_log_file) << "Created at: ";
					const time_t _time = time(NULL);
					(*error_log_file) << asctime(localtime(&_time));
				}
			}
			return error_log_file;
		}
		return get_log_file();
	}

	inline std::ofstream *get_shader_log_file() {
		if(shader_log_filename) {
			if(!shader_log_file) {
				shader_log_file = new std::ofstream(shader_log_filename->c_str());
				if(!shader_log_file->good()) close_shader_log_file();
				else {
					(*shader_log_file) << "Created at: ";
					const time_t _time = time(NULL);
					(*shader_log_file) << asctime(localtime(&_time));
				}
			}
			return shader_log_file;
		}
		return get_log_file();
	}



		/** log **/

	#define LOG(X) std::ofstream *file = get_log_file(); if(file) (*file) << X; std::cout << X; return *this;

	const log_c &log_c::operator<<(cbool val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cshort val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cushort val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cint val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cuint val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(clong val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(culong val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cfloat val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cdouble val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cldouble val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(cvoid *val) const {
		LOG(val)
	}

	const log_c &log_c::operator<<(const std::streambuf* sb) const {
		LOG(sb)
	}

	const log_c &log_c::operator<<(cchar c) const {
		LOG(c)
	}

	const log_c &log_c::operator<<(cschar c) const {
		LOG(c)
	}

	const log_c &log_c::operator<<(cuchar c) const {
		LOG(c)
	}

	const log_c &log_c::operator<<(cchar *s) const {
		LOG(s)
	}

	const log_c &log_c::operator<<(cschar *s) const {
		LOG(s)
	}

	const log_c &log_c::operator<<(cuchar *s) const {
		LOG(s)
	}

	const log_c &log_c::operator<<(std::ostream &(*pf)(std::ostream&)) const {
		LOG(pf)
	}

	const log_c &log_c::operator<<(std::ios &(*pf)(std::ios&)) const {
		LOG(pf)
	}

	const log_c &log_c::operator<<(std::ios_base &(*pf)(std::ios_base&)) const {
		LOG(pf)
	}

	const log_c &log_c::operator<<(const std::string &s) const {
		LOG(s)
	}

	const log_c &log_c::operator<<(const std::exception &e) const {
		LOG(e.what())
	}

	const log_c &log_c::operator<<(const endl_s &e) const {
		(void)e;
		LOG(std::endl)
	}



		/** log_error **/

	#define LOG_ERROR(X) std::ofstream *file = get_error_log_file(); if(file) (*file) << X; std::cerr << X; return *this;

	const log_error_c &log_error_c::operator<<(cbool val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cshort val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cushort val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cint val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cuint val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(clong val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(culong val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cfloat val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cdouble val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cldouble val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(cvoid *val) const {
		LOG_ERROR(val)
	}

	const log_error_c &log_error_c::operator<<(const std::streambuf* sb) const {
		LOG_ERROR(sb)
	}

	const log_error_c &log_error_c::operator<<(cchar c) const {
		LOG_ERROR(c)
	}

	const log_error_c &log_error_c::operator<<(cschar c) const {
		LOG_ERROR(c)
	}

	const log_error_c &log_error_c::operator<<(cuchar c) const {
		LOG_ERROR(c)
	}

	const log_error_c &log_error_c::operator<<(cchar *s) const {
		LOG_ERROR(s)
	}

	const log_error_c &log_error_c::operator<<(cschar *s) const {
		LOG_ERROR(s)
	}

	const log_error_c &log_error_c::operator<<(cuchar *s) const {
		LOG_ERROR(s)
	}

	const log_error_c &log_error_c::operator<<(std::ostream &(*pf)(std::ostream&)) const {
		LOG_ERROR(pf)
	}

	const log_error_c &log_error_c::operator<<(std::ios &(*pf)(std::ios&)) const {
		LOG_ERROR(pf)
	}

	const log_error_c &log_error_c::operator<<(std::ios_base &(*pf)(std::ios_base&)) const {
		LOG_ERROR(pf)
	}

	const log_error_c &log_error_c::operator<<(const std::string &s) const {
		LOG_ERROR(s)
	}

	const log_error_c &log_error_c::operator<<(const std::exception &e) const {
		LOG_ERROR(e.what())
	}

	const log_error_c &log_error_c::operator<<(const endl_s &e) const {
		(void)e;
		LOG_ERROR(std::endl)
	}



		/** log_shader **/

	#define LOG_SHADER(X) std::ofstream *file = get_shader_log_file(); if(file) (*file) << X; std::cerr << X; return *this;

	const log_shader_c &log_shader_c::operator<<(cchar *s) const {
		LOG_SHADER(s)
	}

	const log_shader_c &log_shader_c::operator<<(const endl_s &e) const {
		(void)e;
		LOG_SHADER(std::endl)
	}



		/** print exception **/

	void DLL_EXPORT print_exception(const std::exception &e) {
		#ifdef _WIN32
			const std::string error = std::string("Standard exception: ") + e.what();
			log_error << error << std::endl;
			MessageBox(NULL, error.c_str(), "Error!", MB_ICONWARNING);
		#else
			log_error << "Standard exception: " << e << std::endl;
		#endif
	}

	void DLL_EXPORT print_exception(const std::string &str) {
		log_error << str << std::endl;
		#ifdef _WIN32
			MessageBox(NULL, str.c_str(), "Error!", MB_ICONWARNING);
		#endif
	}

	void DLL_EXPORT print_exception(cchar *str) {
		log_error << str << std::endl;
		#ifdef _WIN32
			MessageBox(NULL, str, "Error!", MB_ICONWARNING);
		#endif
	}



		/** pause **/

	void DLL_EXPORT pause() {
		std::cin.ignore();
	}

}
