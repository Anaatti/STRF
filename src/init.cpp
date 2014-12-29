/** init.cpp **/

#include "init.hpp"
#include "log.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <GL/glew.h>
#include <GL/glfw.h>

namespace strf {

	uchar init_choise = STRF_INIT_DEFAULT;
	bool glew_initialized = false;
	bool initialized = false;
	bool window_opened = false;
	bool resources_initialized = false;

	DLL_EXPORT std::vector<std::pair<uint, uint> > *resolutions = 0;
	DLL_EXPORT std::pair<uint, uint> *desktop_resolution = 0;
	DLL_EXPORT std::pair<uint, uint> *resolution = 0;
	std::pair<uint, uint> *shader_resolution = 0;

	bool resizable = false;
	uchar antialiasing = 4;
	uchar depth_bits = 0;
	uchar stencil_bits = 0;
	std::string *caption = 0;
	std::string *error_string = 0;
	bool vsync = true;
	bool mouse = true;

	void set_anisotrophic_filtering();

	void load_strf_shaders();
	void delete_strf_shaders();

	void load_font();
	void delete_font();

	void init_framebuffers();
	void delete_framebuffers();

	void init_screenshots();
	void uninit_screenshots();

	DLL_EXPORT void DLL_CALL set_log_file(cchar *filename);
	DLL_EXPORT void DLL_CALL set_error_log_file(cchar *filename);
	DLL_EXPORT void DLL_CALL set_shader_log_file(cchar *filename);

	DLL_EXPORT void DLL_CALL init_only(cuchar init) {
		init_choise = init;
	}

	DLL_EXPORT void DLL_CALL init_add(cuchar init) {
		init_choise = init_choise | init;
	}

	DLL_EXPORT void DLL_CALL init_remove(cuchar init) {
		init_choise = init_choise & (~init);
	}

	DLL_EXPORT void DLL_CALL set_resizable(cbool _resizable) {
		resizable = _resizable;
	}

	DLL_EXPORT void DLL_CALL set_antialiasing(cuchar _antialiasing) {
		antialiasing = _antialiasing;
	}

	DLL_EXPORT void DLL_CALL set_depth_bits(cuchar _depth_bits) {
		depth_bits = _depth_bits;
	}

	DLL_EXPORT void DLL_CALL set_stencil_bits(cuchar _stencil_bits) {
		stencil_bits = _stencil_bits;
	}

	DLL_EXPORT void DLL_CALL set_caption(cchar *_caption) {
		if(!caption) caption = new std::string(_caption);
		else caption->assign(_caption);
		if(window_opened) glfwSetWindowTitle(caption->c_str());
	}

	DLL_EXPORT void DLL_CALL set_vsync(cbool _vsync) {
		vsync = _vsync;
		if(window_opened) glfwSwapInterval(vsync ? 1 : 0);
	}

	DLL_EXPORT void DLL_CALL show_mouse(cbool _mouse) {
		mouse = _mouse;
		if(window_opened) {
			if(mouse) glfwEnable(GLFW_MOUSE_CURSOR);
			else glfwDisable(GLFW_MOUSE_CURSOR);
		}
	}

	void set_error_string(cchar *string) {
		if(!error_string) error_string = new std::string(string);
		else error_string->assign(string);
	}

	DLL_EXPORT cchar DLL_CALL *get_error_string() {
		if(!error_string) return "";
		else return error_string->c_str();
	}

	DLL_EXPORT bool DLL_CALL init() {
		if(initialized) return true;

		srand(time(NULL));

		resolutions = new std::vector<std::pair<uint, uint> >;
		desktop_resolution = new std::pair<uint, uint>;
		resolution = new std::pair<uint, uint>;
		shader_resolution = new std::pair<uint, uint>;
		if(!caption) caption = new std::string("STRF program");

		//Init GLFW
		if(glfwInit() == GL_FALSE) {
			if(strf_logging) log_error << "STRF Error: Couldn't initialize GLFW!" << endl;
			initialized = false;
			set_error_string("Couldn't initialize OpenGL Framework");
			return false;
		}

		//Get available video modes
		uchar amount;
		GLFWvidmode list[255];
		amount = glfwGetVideoModes(list, 255);
		for(short i=amount-1;i>=0;i--) {
			if(list[i].RedBits + list[i].GreenBits + list[i].BlueBits == 24) {
				resolutions->push_back(std::pair<uint, uint>(list[i].Width, list[i].Height));
			}
		}
		GLFWvidmode desktop;
		glfwGetDesktopMode(&desktop);
		desktop_resolution->first = desktop.Width;
		desktop_resolution->second = desktop.Height;

		initialized = true;
		return true;
	}

	inline void init_opengl() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}

	DLL_EXPORT void DLL_CALL close_window() {
		if(resources_initialized) {
			delete_strf_shaders();
			delete_font();
			delete_framebuffers();
			uninit_screenshots();
			resources_initialized = false;
		}
		glfwCloseWindow();
		window_opened = false;
	}

	inline bool init_glew() {
		if(!glew_initialized) {
			if(glewInit() != GLEW_OK) {
				if(strf_logging) log_error << "STRF Error: Couldn't initialize GLEW!" << endl;
				set_error_string("Couldn't initialize OpenGL Extension Wrangler");
				return false;
			}
			if(!glewIsSupported("GL_VERSION_2_0")) {
				if(strf_logging) log_error << "STRF Error: OpenGL 2.0 not supported!" << endl;
				set_error_string("OpenGL 2.0 not supported");
				return false;
			}
			glew_initialized = true;
		}
		return true;
	}

	DLL_EXPORT bool DLL_CALL open_window(cushort width, cushort height, cbool fullscreen) {
		if(!initialized) {
			if(!init()) {
				window_opened = false;
				return false;
			}
		}
		if(window_opened) {
			close_window();
			if(strf_logging) log << "STRF: Reopening window" << endl;
		}
		//Load settings
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, resizable ? GL_FALSE : GL_TRUE);
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, antialiasing);
		resolution->first = width;
		resolution->second = height;
		shader_resolution->first = 2;
		shader_resolution->second = 2;
		while(shader_resolution->first < width) shader_resolution->first*= 2;
		while(shader_resolution->second < height) shader_resolution->second*= 2;
		if(glfwOpenWindow(width, height, 8, 8, 8, 8, depth_bits, stencil_bits, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW) == GL_FALSE) {
			if(strf_logging) log_error << "STRF Error: Couldn't open window!" << endl;
			window_opened = false;
			set_error_string("Couldn't open window");
			return false;
		}
		glfwSetWindowPos((desktop_resolution->first - width) / 2, (desktop_resolution->second - height) / 4);
		glfwSetWindowTitle(caption->c_str());
		glfwSwapInterval(vsync ? 1 : 0);
		if(mouse) glfwEnable(GLFW_MOUSE_CURSOR);
		else glfwDisable(GLFW_MOUSE_CURSOR);

		//Check the window parameters
		if(strf_logging) {
			log << "STRF: Using OpenGL version: " << glGetString(GL_VERSION) << endl;
			log << "STRF: Rendering with: " << glGetString(GL_RENDERER) << endl;
			log << (glfwGetWindowParam(GLFW_ACCELERATED) ? "STRF: Hardware accelerated window succesfully opened!" : "STRF: Couldn't get hardware acceleration!") << endl;
			log << "STRF: Color bits: " << (glfwGetWindowParam(GLFW_RED_BITS) + glfwGetWindowParam(GLFW_GREEN_BITS) + glfwGetWindowParam(GLFW_BLUE_BITS) + glfwGetWindowParam(GLFW_ALPHA_BITS)) << " / 32" << endl;
			log << "STRF: Depth bits: " << glfwGetWindowParam(GLFW_DEPTH_BITS) << " / " << (int)depth_bits << endl;
			log << "STRF: Stencil bits: " << glfwGetWindowParam(GLFW_STENCIL_BITS) << " / " << (int)stencil_bits << endl;
			log << "STRF: Multisampling: " << glfwGetWindowParam(GLFW_FSAA_SAMPLES) << " / " << (int)antialiasing << endl;
		}

		window_opened = true;

		//Init GLEW
		if(init_choise & STRF_INIT_GLEW) {
			if(!init_glew()) return false;
		}

		//Init rest
		set_anisotrophic_filtering();
		init_opengl();
		load_strf_shaders();
		load_font();
		init_framebuffers();
		init_screenshots();
		resources_initialized = true;

		return true;
	}

	DLL_EXPORT void DLL_CALL quit() {
		close_window();
		delete resolutions;
		resolutions = 0;
		delete desktop_resolution;
		desktop_resolution = 0;
		delete resolution;
		resolution = 0;
		delete shader_resolution;
		shader_resolution = 0;
		delete caption;
		caption = 0;
		delete error_string;
		error_string = 0;
		set_log_file(0);
		set_error_log_file(0);
		set_shader_log_file(0);
		glfwTerminate();
		initialized = false;
	}

}
