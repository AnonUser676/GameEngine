#include "Application.h"

namespace VirtualStage {

	static const double NANO_TO_SECONDS = 0.000000001;

	static const ullong NANO_IN_SECONDS = 1000000000ULL;


	Application::Application() : window(nullptr), engineRunning(true), fps(0)
	{
	}


	Application::~Application()
	{
	}

	void Application::AppRun(const char* title, int width, int height, bool fullscreen)
	{
		if (createWindow(title, width, height, fullscreen) && startUp())
		{
			frames = 0;
			fpsInterval = 0;

			while (engineRunning)
			{
				m_previousTime = m_currentTime;
				m_currentTime = m_clock.now();
				auto duration = m_currentTime - m_previousTime;
				float deltaTime = duration.count() * NANO_TO_SECONDS;

				currTime = glfwGetTime();
				DeltaTime = currTime - prevTime;
				prevTime = currTime;

				std::cout << currTime << std::endl;
				std::cout << DeltaTime << std::endl;
				std::cout << deltaTime << std::endl;
				std::cout << prevTime << std::endl;

				glfwPollEvents(); //poll events

				// skip if minimised
				if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
					continue;

				frames++;
				fpsInterval += deltaTime;
				if (fpsInterval >= 1.0f) {
					fps = frames;
					frames = 0;
					fpsInterval -= 1.0f;
				}

				update(float(deltaTime));

				draw();

				glfwSwapBuffers(window); //swap buffers

				if (glfwWindowShouldClose(window))
				{
					std::cout << "windown has closed" << std::endl;
				}

				// should the game exit?
				engineRunning = engineRunning || glfwWindowShouldClose(window) == GLFW_TRUE;
			}
		}
		shutDown();
		destroyWindow();
	}

	bool Application::createWindow(const char* title, int width, int height, bool fullscreen)
	{
		if (!glfwInit())
		{
			std::cout << "glfw did not Initialize" << std::endl;
			return false;
		}

		GLFWmonitor** screens;
		int count = 0;
		screens = glfwGetMonitors(&count);
		std::cout << count << std::endl;

		//window and GPU linkage
		window = glfwCreateWindow(width, height, title, (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);

		//checks if window is running or has failed
		if (window == nullptr)
		{
			std::cout << "window has failed to load" << std::endl;
			glfwTerminate(); //terminates connection to graphics card if window fails
			return false;
		}

		glfwMakeContextCurrent(window); //creates window create context


		//checks if all functions passed is legal
		if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
			std::cout << "OGL Has Failed to Load" << std::endl;
			return false;
		}


		//get ogl version and print
		auto major = ogl_GetMajorVersion();
		auto minor = ogl_GetMinorVersion();
		std::cout << "GL: " << major << "." << minor << std::endl;

		glfwSetWindowSizeCallback(window, [](GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); });

		//function to clear colors
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		//enable depth
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//create Gizmo
		aie::Gizmos::create(10000, 10000, 10000, 10000);

		////sets up camera
		////create view size for camera window
		//view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
		////create projection window
		//projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

		prevTime = glfwGetTime();
		currTime = 0;
		DeltaTime = 0;

		m_startTime = m_clock.now();
		m_currentTime = m_clock.now();
		m_previousTime = m_clock.now();

		return true;
	}

	//bool Application::update()
	//{
		//if (glfwWindowShouldClose(window))
		//{
		//	std::cout << "windown has closed" << std::endl;
		//	return false;
		//}

		//m_previousTime = m_currentTime;
		//m_currentTime = m_clock.now();
		//auto duration = m_currentTime - m_previousTime;
		//float deltaTime = duration.count() * NANO_TO_SECONDS;

		//currTime = glfwGetTime();
		//DeltaTime = currTime - prevTime;
		//prevTime = currTime;

		//std::cout << currTime << std::endl;
		//std::cout << DeltaTime << std::endl;
		//std::cout << deltaTime << std::endl;
		//std::cout << prevTime << std::endl;


		//glfwSwapBuffers(window); //swap buffers
		//glfwPollEvents(); //poll events

		//return true;
	//}

	void Application::clearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Application::setBackGroundColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Application::setCursorVisible(bool visible)
	{
		ShowCursor(visible);
	}

	void Application::setVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
	}

	bool Application::windowHasClosed()
	{
		return  glfwWindowShouldClose(window) == GL_TRUE;
	}

	unsigned int Application::getWindowWidth() const
	{
		int w = 0, h = 0;
		glfwGetWindowSize(window, &w, &h);
		return w;
	}

	unsigned int Application::getWindowHeight() const 
	{
		int w = 0, h = 0;
		glfwGetWindowSize(window, &w, &h);
		return w;
	}

	//void Application::draw()
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	//game logic and update goes here
	//	//render code begins here

	//	aie::Gizmos::clear();
	//	//adds 3-axis line 
	//	aie::Gizmos::addTransform(glm::mat4(1));

	//	vec4 white(1);
	//	vec4 black(0, 0, 0, 1);

	//	//for drawing grid
	//	for (int i = 0; i < 21; i++)
	//	{
	//		aie::Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);

	//		aie::Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	//	}

	//	//iniitiate draw with camera set-up by projection and view values
	//	aie::Gizmos::draw(projection * view);
	//}

	void Application::destroyWindow()
	{
		//closes gizmo
		aie::Gizmos::destroy();

		//destroys window afterwards
		glfwDestroyWindow(window);
		//stops connecting to Graphics card
		glfwTerminate();
	}

}