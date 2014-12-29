/** main.cpp **/

#include <iostream>
#include <fstream>
#include <cstring>

#define FONT_SIZE 64
#define FONT_COUNT 16

unsigned char *load_png(const char *filename, unsigned int &width, unsigned int &height, unsigned int &_channels);
bool SavePNG(const char* FilePath, const unsigned char *m_pImageData, const unsigned int m_Width, const unsigned int m_Height, const unsigned int channels);

unsigned char *load_file(const char *path, unsigned int &len) {
	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
	if(file.good()) {
		len = file.tellg();
		file.seekg(0, std::ios::beg);
		unsigned char *data = new unsigned char[len];
		file.read((char*)data, len);
		file.close();
		return data;
	}
	std::cerr << "Couldn't load file " << path << "!" << std::endl;
	return 0;
}

int main() {
	unsigned int width, height, channels;
	unsigned char *image = load_png("font.png", width, height, channels);
	width = FONT_SIZE;
	height = FONT_SIZE;
	channels = 4;
	for(unsigned short a=0;a<256;a++) {
		if(a % 2) std::cout << ".";
		unsigned char *pixels = new unsigned char[FONT_SIZE * FONT_SIZE * 4];
		const unsigned short xoffset = (a % FONT_COUNT) * FONT_SIZE;
		const unsigned short yoffset = (15 - a / FONT_COUNT) * FONT_SIZE;
		for(unsigned short x=0;x<FONT_SIZE;x++) {
			for(unsigned short y=0;y<FONT_SIZE;y++) {
				const unsigned int pos1 = (y * FONT_SIZE + x) * 4;
				const unsigned int pos2 = ((y + yoffset) * FONT_SIZE * FONT_COUNT + x + xoffset) * 4;
				pixels[pos1] = 255;
				pixels[pos1 + 1] = 255;
				pixels[pos1 + 2] = 255;
				pixels[pos1 + 3] = image[pos2 + 3];
			}
		}
		char outputname[256];
		sprintf(outputname, "chars/%03i.png", a);
		SavePNG(outputname, pixels, width, height, channels);
		//Done
		delete [] pixels;
	}
	delete [] image;

	std::cout << std::endl;

	std::ofstream file("text_data.dat");
	unsigned char *empty = 0;
	unsigned int empty_len = 0;
	for(unsigned short a=0;a<256;a++) {
		if(a % 2) std::cout << ".";
		char outputname[256];
		sprintf(outputname, "chars/%03i.png", a);
		unsigned int len;
		unsigned char *data = load_file(outputname, len);

		if(!a) {
			empty_len = len;
			empty = new unsigned char[empty_len];
			memcpy(empty, data, len);
		}

		if(a && len == empty_len && memcmp(data, empty, empty_len) == 0) {
			file << "init_character(pixels0," << a << "," << empty_len << ");\n";
		}
		else {
			file << "uchar pixels" << a << "[" << len << "]={" << (len > 20 ? "\n" : "") << (int)data[0];
			for(unsigned int i=1;i<len;i++) file << "," << (i % 20 ? "" : "\n") << (int)data[i];
			file << "};\ninit_character(pixels" << a << "," << a << "," << len << ");\n";
		}

		delete [] data;
	}
	delete [] empty;
	file.close();

	std::cout << " done" << std::endl;

	std::cin.ignore();
	return 0;
}
