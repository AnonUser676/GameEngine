#pragma once
#include <iostream>
#include <glm.hpp>
#include <ext.hpp>
#include "../Dependencies/glCore/gl_core_4_5.h"
#include <glfw3.h>
#include "Gizmos.h"
#include <chrono>

using glm::mat4;
using glm::vec3;
using glm::vec4;
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;

namespace my
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
}

namespace VirtualStage {
	class Application
	{
	public:
		Application();
		~Application();

		void AppRun(const char* title, int width, int height, bool fullscreen);

		virtual bool startUp() = 0;
		virtual void shutDown() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;

		void clearScreen();
		void setBackGroundColor(float r, float g, float b, float a = 1.0f);
		void setCursorVisible(bool visible);
		void setVSync(bool enabled);
		void quit() { engineRunning = false; }
		GLFWwindow* getWindowPtr() const { return window; }
		bool windowHasClosed();
		unsigned int getFPS() const { return fps; }

		unsigned int getWindowWidth() const;
		unsigned int getWindowHeight() const;

	protected:
		bool createWindow(const char* title, int width, int height, bool fullscreen);
		void destroyWindow();

		GLFWwindow* window;
		double prevTime;
		double currTime;
		double DeltaTime;
		unsigned int frames;
		double fpsInterval;

		bool engineRunning;
		unsigned int fps;

		my::clock m_clock;
		my::time m_startTime;
		my::time m_currentTime;
		my::time m_previousTime;
	};

}