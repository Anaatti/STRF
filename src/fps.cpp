/** fps.cpp **/

#include "fps.hpp"
#include <GL/glfw.h>

namespace strf {

	DLL_EXPORT void DLL_CALL draw_float(cfloat value, cuchar precision, cfloat x, cfloat y, cfloat size, cuchar align);

	extern DLL_EXPORT double top_edge;
	extern DLL_EXPORT double left_edge;

	bool draw_fps = false;
	float fps_draw_size = 30;

	DLL_EXPORT void DLL_CALL set_fps_draw(cbool value) {
		draw_fps = value;
	}

	DLL_EXPORT void DLL_CALL set_fps_draw_size(cfloat value) {
		fps_draw_size = value;
	}

	fps::fps(cdouble new_fps):
		delay(1.0 / new_fps),
		time(glfwGetTime()),
		timestamp(time),
		undrawn_count(0),
		drew_previous_frame(0) {
		for(ushort i=0;i<new_fps;i++) real_delays.push_back(delay);
		for(ushort i=0;i<new_fps;i++) delays.push_back(delay * 0.66); // ~ around 1.5 times the requested fps
		for(ushort i=0;i<new_fps/5;i++) sleeps.push_back(delay - delay * 0.66);
	}

	void fps::draw() const {
		if(!draw_fps) return;
		//drawn real fps
		float drawn_real_fps = 10000;
		float fps_sum = 0;
		for(std::deque<double>::const_iterator i=real_delays.begin();i!=real_delays.end();i++) fps_sum+= *i;
		if(fps_sum != 0.0) drawn_real_fps = (float)real_delays.size() / fps_sum;
		//drawn fps
		float drawn_fps = 10000;
		fps_sum = 0;
		for(std::deque<double>::const_iterator i=delays.begin();i!=delays.end();i++) fps_sum+= *i;
		if(fps_sum != 0.0) drawn_fps = (float)delays.size() / fps_sum;
		//drawn sleep
		fps_sum = 0;
		for(std::deque<double>::const_iterator i=sleeps.begin();i!=sleeps.end();i++) fps_sum+= *i;
		float drawn_sleep = fps_sum / (float)sleeps.size();
		glColor4f(drew_previous_frame ? 0.8 : 0.0, drew_previous_frame == 2 ? 0.0 : 0.8, 0.0, 1.0);
		draw_float(drawn_real_fps, 1, strf::left_edge + fps_draw_size * 3.75, strf::top_edge + fps_draw_size * 0.125, fps_draw_size, 2);
		draw_float(drawn_fps, 1, strf::left_edge + fps_draw_size * 3.75, strf::top_edge + fps_draw_size * 1.25, fps_draw_size, 2);
		draw_float(drawn_sleep, 3, strf::left_edge + fps_draw_size * 3.75, strf::top_edge + fps_draw_size * 2.375, fps_draw_size, 2);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}

	void fps::wait() {
		time+= delay;
		cdouble get_time = glfwGetTime();
		cdouble sleep = time - get_time;
		//sleep and reset
		if(sleep > 0) glfwSleep(sleep);
		else if(sleep < -0.4) time = glfwGetTime();
		//skip frames
		drew_previous_frame = undrawn_count;
		if(sleep < -0.2) undrawn_count = (undrawn_count + 1) % 3;
		else if(sleep < -0.1) undrawn_count = 1 - undrawn_count;
		else undrawn_count = 0;
		//draw info
		real_delays.pop_front();
		real_delays.push_back(get_time - timestamp);
		delays.pop_front();
		delays.push_back(delay - sleep);
		sleeps.pop_front();
		sleeps.push_back(sleep);
		timestamp = get_time; //remember this
	}

	void fps::reset() {
		time = glfwGetTime();
	}

	bool fps::draw_frame() const {
		return !undrawn_count;
	}

}
