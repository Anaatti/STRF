/** web.cpp **/

#include "global.hpp"
#ifdef _WIN32
	#include <windows.h>
#else
	#include <cstdlib>
	#include <string>
#endif

namespace strf {

	DLL_EXPORT void DLL_CALL open_website(cchar *site) {
		#ifdef _WIN32
			ShellExecute(NULL, "open", site, NULL, NULL, SW_SHOWNORMAL);
		#else
			std::string temp("xdg-open '");
			temp+= site;
			temp+= "'";
			system(temp.c_str()); //Attempts to open a website on Linux but may not work on all distros
		#endif
	}

}
