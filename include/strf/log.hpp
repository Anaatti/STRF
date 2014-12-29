/** log.hpp **/

#ifndef STRF_LOG_HPP
#define STRF_LOG_HPP

#include <strf/global.hpp>
#include <streambuf>
#include <ostream>

namespace strf {

	void DLL_EXPORT print_exception(const std::exception &e);
	void DLL_EXPORT print_exception(const std::string &str);
	void DLL_EXPORT print_exception(cchar *str);
	void DLL_EXPORT pause();

	struct DLL_EXPORT endl_s {};
	extern DLL_EXPORT endl_s endl;

	struct DLL_EXPORT log_c {
		public:
			const log_c &operator<<(cbool val) const;
			const log_c &operator<<(cshort val) const;
			const log_c &operator<<(cushort val) const;
			const log_c &operator<<(cint val) const;
			const log_c &operator<<(cuint val) const;
			const log_c &operator<<(clong val) const;
			const log_c &operator<<(culong val) const;
			const log_c &operator<<(cfloat val) const;
			const log_c &operator<<(cdouble val) const;
			const log_c &operator<<(cldouble val) const;
			const log_c &operator<<(cvoid *val) const;
			const log_c &operator<<(const std::streambuf* sb) const;
			const log_c &operator<<(cchar c) const;
			const log_c &operator<<(cschar c) const;
			const log_c &operator<<(cuchar c) const;
			const log_c &operator<<(cchar *s) const;
			const log_c &operator<<(cschar *s) const;
			const log_c &operator<<(cuchar *s) const;
			const log_c &operator<<(std::ostream &(*pf)(std::ostream&)) const;
			const log_c &operator<<(std::ios &(*pf)(std::ios&)) const;
			const log_c &operator<<(std::ios_base &(*pf)(std::ios_base&)) const;
			const log_c &operator<<(const std::string &s) const;
			const log_c &operator<<(const std::exception &e) const;
			const log_c &operator<<(const endl_s &e) const;
	};

	struct DLL_EXPORT log_error_c {
		public:
			const log_error_c &operator<<(cbool val) const;
			const log_error_c &operator<<(cshort val) const;
			const log_error_c &operator<<(cushort val) const;
			const log_error_c &operator<<(cint val) const;
			const log_error_c &operator<<(cuint val) const;
			const log_error_c &operator<<(clong val) const;
			const log_error_c &operator<<(culong val) const;
			const log_error_c &operator<<(cfloat val) const;
			const log_error_c &operator<<(cdouble val) const;
			const log_error_c &operator<<(cldouble val) const;
			const log_error_c &operator<<(cvoid *val) const;
			const log_error_c &operator<<(const std::streambuf* sb) const;
			const log_error_c &operator<<(cchar c) const;
			const log_error_c &operator<<(cschar c) const;
			const log_error_c &operator<<(cuchar c) const;
			const log_error_c &operator<<(cchar *s) const;
			const log_error_c &operator<<(cschar *s) const;
			const log_error_c &operator<<(cuchar *s) const;
			const log_error_c &operator<<(std::ostream &(*pf)(std::ostream&)) const;
			const log_error_c &operator<<(std::ios &(*pf)(std::ios&)) const;
			const log_error_c &operator<<(std::ios_base &(*pf)(std::ios_base&)) const;
			const log_error_c &operator<<(const std::string &s) const;
			const log_error_c &operator<<(const std::exception &e) const;
			const log_error_c &operator<<(const endl_s &e) const;
	};

	extern DLL_EXPORT log_c log;
	extern DLL_EXPORT log_error_c log_error;

}

#endif
