/** input.cpp **/

#include "global.hpp"
#include <GL/glfw.h>

namespace strf {

	DLL_EXPORT bool DLL_CALL window_opened() {
		return glfwGetWindowParam(GLFW_OPENED);
	}

	DLL_EXPORT bool DLL_CALL window_closed() {
		return !glfwGetWindowParam(GLFW_OPENED);
	}

	DLL_EXPORT bool DLL_CALL window_active() {
		return glfwGetWindowParam(GLFW_ACTIVE);
	}

	DLL_EXPORT bool DLL_CALL window_inactive() {
		return !glfwGetWindowParam(GLFW_ACTIVE);
	}

	DLL_EXPORT int DLL_CALL get_key(cint key) {
		return glfwGetKey(key);
	}

	DLL_EXPORT int DLL_CALL get_mouse_button(cint button) {
		return glfwGetMouseButton(button);
	}

	DLL_EXPORT void DLL_CALL get_mouse_position(int *xpos, int *ypos) {
		glfwGetMousePos(xpos, ypos);
	}

	DLL_EXPORT void DLL_CALL set_mouse_position(cint xpos, cint ypos) {
		glfwSetMousePos(xpos, ypos);
	}

	DLL_EXPORT int DLL_CALL get_mouse_wheel() {
		return glfwGetMouseWheel();
	}

	DLL_EXPORT void DLL_CALL set_mouse_wheel(cint pos) {
		glfwSetMouseWheel(pos);
	}

	DLL_EXPORT double DLL_CALL get_time() {
		return glfwGetTime();
	}

	DLL_EXPORT void DLL_CALL sleep(cdouble time) {
		glfwSleep(time);
	}

}
