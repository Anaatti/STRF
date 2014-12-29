#include <strf/init.hpp>
#include <strf/log.hpp>
#include <strf/texture.hpp>
#include <strf/shader.hpp>
#include <strf/fbo.hpp>
#include <strf/fps.hpp>
#include <strf/draw.hpp>
#include <strf/text.hpp>
#include <strf/input.hpp>
#include <strf/screenshot.hpp>
#include <cmath>

int main(int argc, char **argv) {
	(void)argc; (void)argv;
	try {
		// Don't init the old framebuffer-functionality because we use FBOs instead
		strf::init_remove(STRF_INIT_FRAMEBUFFER);
		// Set some graphics and window options
		strf::set_antialiasing(16);
		strf::set_vsync(true);
		strf::set_caption("Example");
		strf::set_resizable(false);
		// Set default texture options
		strf::set_texture_wrap(GL_CLAMP);
		strf::set_texture_filter(GL_LINEAR);
		strf::set_texture_mipmap(STRF_MIPMAP_SOME); // Mipmaps will be created for textures with power of 2 dimensions
		// Draw FPS
		strf::set_fps_draw(true);
		strf::set_fps_draw_size(40);
		// Set log-files
		strf::set_log_file("log.txt");
		strf::set_shader_log_file("log_shaders.txt");
		// Init and open window
		if(!strf::init()) throw strf::get_error_string();
		if(!strf::open_window(512, 512)) throw strf::get_error_string();
		// Set the 2D-projection matrix here
		strf::set_default_aspect(1);
		strf::set_default_projection(512, 512);

		glClearColor(1.0, 0.0, 0.0, 0.0);

		strf::log << "Logging example" << strf::endl;

		// Textures, shaders and FBOs will get freed at the end of this block
		{
			strf::texture tex("images/example.png");

			// Load a shader from two files and include the built-in random number generator
			strf::shader effect("shaders/example.vert", "shaders/example.frag", true);
			// Define two uniforms for the shader
			effect.add_uniform(STRF_VEC2, "time");
			effect.add_uniform(STRF_FLOAT, "amount");

			strf::fbo framebuffer2;
			strf::fbo framebuffer; // This FBO will automatically be the drawing target now

			// Create the fps-handler using 15 fps
			strf::fps fps(15);
			uint framecount = 0;

			// Loop until the window is closed or the esc-key is pressed
			while(strf::window_opened() && !strf::get_key(GLFW_KEY_ESC)) {
				framecount++;

				// Ask the fps-class if the frame should be skipped due to long render times
				if(fps.draw_frame()) {
					// Restore the 2D-projection matrix defined earlier
					strf::set_default_projection();
					// Draw to an FBO
					framebuffer();
					// Use the built-in shader for texturing
					strf::basic_shader->use();

					// Draw some images and text
					// Using the strf-edges here, the image will always fill the whole viewport in every case
					strf::draw_image(tex, strf::right_edge, strf::top_edge,
						strf::left_edge - strf::right_edge, strf::bottom_edge - strf::top_edge);
					glColor4f(0.0, 0.0, 0.0, 1.0);
					strf::draw_text("Example", 256, 64, 60, 1);
					strf::draw_vertical_text("Example", 64, 448, 60, 0);
					fps.draw();

					glColor4f(1.0, 1.0, 1.0, 1.0);

					// Draw the contents of the first FBO to the second one
					framebuffer2();
					framebuffer.draw();

					// Draw the contents of the second FBO back to the first one using a cool shader
					// The first two values sent to the shader will go to the 'vec2 time'; the third value will set the 'float amount'
					effect << framecount << framecount + 1 << float(sin((float)framecount / 8.0) * 2.0 + 10.0);
					framebuffer();
					framebuffer2.draw();

					// Draw the contents of the first FBO to the screen buffer to make it actually visible
					strf::basic_shader->use();
					strf::use_fbo_0();
					framebuffer.draw();

					// Swap the buffer or just poll events depending on whether something was drawn
					strf::swap_frame();
				}
				else strf::poll_events();

				// Wait some time to get the requested fps
				fps.wait();
			}

			// Take a screenshot at the end
			// Note that this screenshot will probably not work very well at this point if the program is not closed using the esc-key
			strf::screenshot->take_screenshot(0);
		}

		strf::quit();
		return 0;
	}
	catch(cchar *str) { // This catches the strf-errors thrown from initialization
		strf::print_exception(str);
	}
	catch(const std::exception &e) {
		strf::print_exception(e);
	}
	catch(...) {
		strf::print_exception("An unknown error occurred!");
	}
}
