/** input.hpp **/

#ifndef STRF_INPUT_HPP
#define STRF_INPUT_HPP

#include <strf/global.hpp>

#define GLFW_KEY_UNKNOWN      -1
#define GLFW_KEY_SPACE        32
#define GLFW_KEY_SPECIAL      256
#define GLFW_KEY_ESC          (GLFW_KEY_SPECIAL+1)
#define GLFW_KEY_F1           (GLFW_KEY_SPECIAL+2)
#define GLFW_KEY_F2           (GLFW_KEY_SPECIAL+3)
#define GLFW_KEY_F3           (GLFW_KEY_SPECIAL+4)
#define GLFW_KEY_F4           (GLFW_KEY_SPECIAL+5)
#define GLFW_KEY_F5           (GLFW_KEY_SPECIAL+6)
#define GLFW_KEY_F6           (GLFW_KEY_SPECIAL+7)
#define GLFW_KEY_F7           (GLFW_KEY_SPECIAL+8)
#define GLFW_KEY_F8           (GLFW_KEY_SPECIAL+9)
#define GLFW_KEY_F9           (GLFW_KEY_SPECIAL+10)
#define GLFW_KEY_F10          (GLFW_KEY_SPECIAL+11)
#define GLFW_KEY_F11          (GLFW_KEY_SPECIAL+12)
#define GLFW_KEY_F12          (GLFW_KEY_SPECIAL+13)
#define GLFW_KEY_F13          (GLFW_KEY_SPECIAL+14)
#define GLFW_KEY_F14          (GLFW_KEY_SPECIAL+15)
#define GLFW_KEY_F15          (GLFW_KEY_SPECIAL+16)
#define GLFW_KEY_F16          (GLFW_KEY_SPECIAL+17)
#define GLFW_KEY_F17          (GLFW_KEY_SPECIAL+18)
#define GLFW_KEY_F18          (GLFW_KEY_SPECIAL+19)
#define GLFW_KEY_F19          (GLFW_KEY_SPECIAL+20)
#define GLFW_KEY_F20          (GLFW_KEY_SPECIAL+21)
#define GLFW_KEY_F21          (GLFW_KEY_SPECIAL+22)
#define GLFW_KEY_F22          (GLFW_KEY_SPECIAL+23)
#define GLFW_KEY_F23          (GLFW_KEY_SPECIAL+24)
#define GLFW_KEY_F24          (GLFW_KEY_SPECIAL+25)
#define GLFW_KEY_F25          (GLFW_KEY_SPECIAL+26)
#define GLFW_KEY_UP           (GLFW_KEY_SPECIAL+27)
#define GLFW_KEY_DOWN         (GLFW_KEY_SPECIAL+28)
#define GLFW_KEY_LEFT         (GLFW_KEY_SPECIAL+29)
#define GLFW_KEY_RIGHT        (GLFW_KEY_SPECIAL+30)
#define GLFW_KEY_LSHIFT       (GLFW_KEY_SPECIAL+31)
#define GLFW_KEY_RSHIFT       (GLFW_KEY_SPECIAL+32)
#define GLFW_KEY_LCTRL        (GLFW_KEY_SPECIAL+33)
#define GLFW_KEY_RCTRL        (GLFW_KEY_SPECIAL+34)
#define GLFW_KEY_LALT         (GLFW_KEY_SPECIAL+35)
#define GLFW_KEY_RALT         (GLFW_KEY_SPECIAL+36)
#define GLFW_KEY_TAB          (GLFW_KEY_SPECIAL+37)
#define GLFW_KEY_ENTER        (GLFW_KEY_SPECIAL+38)
#define GLFW_KEY_BACKSPACE    (GLFW_KEY_SPECIAL+39)
#define GLFW_KEY_INSERT       (GLFW_KEY_SPECIAL+40)
#define GLFW_KEY_DEL          (GLFW_KEY_SPECIAL+41)
#define GLFW_KEY_PAGEUP       (GLFW_KEY_SPECIAL+42)
#define GLFW_KEY_PAGEDOWN     (GLFW_KEY_SPECIAL+43)
#define GLFW_KEY_HOME         (GLFW_KEY_SPECIAL+44)
#define GLFW_KEY_END          (GLFW_KEY_SPECIAL+45)
#define GLFW_KEY_KP_0         (GLFW_KEY_SPECIAL+46)
#define GLFW_KEY_KP_1         (GLFW_KEY_SPECIAL+47)
#define GLFW_KEY_KP_2         (GLFW_KEY_SPECIAL+48)
#define GLFW_KEY_KP_3         (GLFW_KEY_SPECIAL+49)
#define GLFW_KEY_KP_4         (GLFW_KEY_SPECIAL+50)
#define GLFW_KEY_KP_5         (GLFW_KEY_SPECIAL+51)
#define GLFW_KEY_KP_6         (GLFW_KEY_SPECIAL+52)
#define GLFW_KEY_KP_7         (GLFW_KEY_SPECIAL+53)
#define GLFW_KEY_KP_8         (GLFW_KEY_SPECIAL+54)
#define GLFW_KEY_KP_9         (GLFW_KEY_SPECIAL+55)
#define GLFW_KEY_KP_DIVIDE    (GLFW_KEY_SPECIAL+56)
#define GLFW_KEY_KP_MULTIPLY  (GLFW_KEY_SPECIAL+57)
#define GLFW_KEY_KP_SUBTRACT  (GLFW_KEY_SPECIAL+58)
#define GLFW_KEY_KP_ADD       (GLFW_KEY_SPECIAL+59)
#define GLFW_KEY_KP_DECIMAL   (GLFW_KEY_SPECIAL+60)
#define GLFW_KEY_KP_EQUAL     (GLFW_KEY_SPECIAL+61)
#define GLFW_KEY_KP_ENTER     (GLFW_KEY_SPECIAL+62)
#define GLFW_KEY_KP_NUM_LOCK  (GLFW_KEY_SPECIAL+63)
#define GLFW_KEY_CAPS_LOCK    (GLFW_KEY_SPECIAL+64)
#define GLFW_KEY_SCROLL_LOCK  (GLFW_KEY_SPECIAL+65)
#define GLFW_KEY_PAUSE        (GLFW_KEY_SPECIAL+66)
#define GLFW_KEY_LSUPER       (GLFW_KEY_SPECIAL+67)
#define GLFW_KEY_RSUPER       (GLFW_KEY_SPECIAL+68)
#define GLFW_KEY_MENU         (GLFW_KEY_SPECIAL+69)
#define GLFW_KEY_LAST         GLFW_KEY_MENU

#define GLFW_MOUSE_BUTTON_1      0
#define GLFW_MOUSE_BUTTON_2      1
#define GLFW_MOUSE_BUTTON_3      2
#define GLFW_MOUSE_BUTTON_4      3
#define GLFW_MOUSE_BUTTON_5      4
#define GLFW_MOUSE_BUTTON_6      5
#define GLFW_MOUSE_BUTTON_7      6
#define GLFW_MOUSE_BUTTON_8      7
#define GLFW_MOUSE_BUTTON_LAST   GLFW_MOUSE_BUTTON_8

#define GLFW_MOUSE_BUTTON_LEFT   GLFW_MOUSE_BUTTON_1
#define GLFW_MOUSE_BUTTON_RIGHT  GLFW_MOUSE_BUTTON_2
#define GLFW_MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_3

namespace strf {
	DLL_EXPORT void DLL_CALL poll_events();
	DLL_EXPORT bool DLL_CALL window_opened();
	DLL_EXPORT bool DLL_CALL window_closed();
	DLL_EXPORT bool DLL_CALL window_active();
	DLL_EXPORT bool DLL_CALL window_inactive();
	DLL_EXPORT int DLL_CALL get_key(cint key);
	DLL_EXPORT int DLL_CALL get_mouse_button(cint button);
	DLL_EXPORT void DLL_CALL get_mouse_position(int *xpos, int *ypos);
	DLL_EXPORT void DLL_CALL set_mouse_position(cint xpos, cint ypos);
	DLL_EXPORT int DLL_CALL get_mouse_wheel();
	DLL_EXPORT void DLL_CALL set_mouse_wheel(cint pos);
	DLL_EXPORT double DLL_CALL get_time();
	DLL_EXPORT void DLL_CALL sleep(cdouble time);
}

#endif
