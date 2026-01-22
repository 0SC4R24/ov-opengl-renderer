#pragma once

#include "common.h"

namespace old
{
	typedef struct 
	{
		double xPos, yPos;
		std::map<int, bool> buttonState;
	} mouseState_t;

	class GLFWKeyManager
	{
	public:
		static inline GLFWwindow* window;

		static inline std::map<int, bool> keyboardState;
		static inline mouseState_t mouseState = { 0,0 };
		static void initKeyManager(GLFWwindow* window);
		static void windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mousePosEvent(GLFWwindow* window, double xPos, double yPos);
		static void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
		static void updateEvents();
		static void setCursorPos(double x, double y);
	};
};