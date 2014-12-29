/** resolution.hpp **/

#ifndef STRF_RESOLUTION_HPP
#define STRF_RESOLUTION_HPP

#include <strf/global.hpp>
#include <vector>

namespace strf {
	extern DLL_EXPORT std::vector<std::pair<uint, uint> > *resolutions;
	extern DLL_EXPORT std::pair<uint, uint> *desktop_resolution;
	extern DLL_EXPORT std::pair<uint, uint> *resolution;

	extern DLL_EXPORT double top_edge;
	extern DLL_EXPORT double bottom_edge;
	extern DLL_EXPORT double left_edge;
	extern DLL_EXPORT double right_edge;
}

#endif
