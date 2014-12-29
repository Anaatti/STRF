/** load_texture.cpp **/

#include "load_texture.hpp"
#include "log.hpp"
#include <fstream>

namespace strf {

	DLL_EXPORT bitmap* DLL_CALL load_texture(cchar *path) {
		try {
			std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
			if(!file.good()) {
				if(strf_logging) log_error << "STRF Error: Couldn't load texture from " << path << "!" << endl;
				file.close();
				return 0;
			}
			cint size = file.tellg();
			file.seekg(0, std::ios::beg);
			uchar *content = new uchar[size];
			file.read((char*)content, size);
			file.close();

			bitmap *map = 0;
			try {
				if(content[0] == 'B' && content[1] == 'M') map = parse_bmp(content);
				else if(content[1] == 'P' && content[2] == 'N' && content[3] == 'G') map = parse_png(content, size);
				else if(strf_logging) log_error << "STRF Error: " << path << " is not of a supported file format" << endl;
			}
			catch(const std::exception &e) {
				if(strf_logging) {
					log_error << "STRF Error: Standard exception while parsing the image: " << path << endl;
					print_exception(e);
				}
			}
			delete [] content;
			return map;
		}
		catch(const std::exception &e) {
			if(strf_logging) {
				log_error << "STRF Error: Standard exception while loading the image: " << path << endl;
				print_exception(e);
			}
			return 0;
		}
	}

}
