/** text_load.cpp **/

#include "texture.hpp"
#include "load_texture.hpp"
#include "log.hpp"

namespace strf {

	extern DLL_EXPORT texture *font[256];

	void init_character(uchar *data, cuchar id, cuint size) {
		try {
			font[id] = new texture(parse_png(data, size));
		}
		catch(const std::exception &e) {
			if(strf_logging) {
				log_error << "STRF Error: Standard exception while loading font: the character " << (int)id << " (" << id << ")" << endl;
				print_exception(e);
			}
		}
	}

	void init_font() {
		#include "text_data.dat"
	}

}
