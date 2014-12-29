/** fps.hpp **/

#ifndef FPS_HPP
#define FPS_HPP

#include "global.hpp"
#include <deque>

namespace strf {

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
