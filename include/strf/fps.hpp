/** fps.hpp **/

#ifndef STRF_FPS_HPP
#define STRF_FPS_HPP

#include <strf/global.hpp>
#include <deque>

namespace strf {

	#ifndef STRF_INIT_HPP
	DLL_EXPORT void DLL_CALL set_fps_draw_size(cfloat value = 40.0);
	#endif

	class DLL_EXPORT fps {
		private:
			fps(const fps &fps); //Copy constructor
			fps &operator=(const fps &fps); //Assign operator
			cdouble delay;
			double time;
			double timestamp;
			uchar undrawn_count;
			uchar drew_previous_frame;
			std::deque<double> real_delays;
			std::deque<double> delays;
			std::deque<double> sleeps;

		public:
			fps(cdouble new_fps);
			void draw() const;
			void wait();
			void reset();
			bool draw_frame() const;
	};

}

#endif
