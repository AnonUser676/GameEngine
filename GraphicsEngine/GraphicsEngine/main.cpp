#include "ApplicationEngine.h"
//#include <iostream>
//#include <glm.hpp>
//#include <ext.hpp>
//#include "../Dependencies/glCore/gl_core_4_5.h"
//#include <glfw3.h>
//#include "Gizmos.h"
//
//using glm::mat4;
//using glm::vec3;
//using glm::vec4;

int main()
{
	//check if Graphics card is active
	//if (!glfwInit())
	//	return -1;

	//GLFWmonitor** screens;
	//int count = 0;
	//screens = glfwGetMonitors(&count);
	//std::cout << count << std::endl;

	////window and GPU linkage
	//GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	////checks if window is running or has failed
	//if (window == nullptr)
	//{
	//	glfwTerminate(); //terminates connection to graphics card if window fails
	//	return -2;
	//}

	//glfwMakeContextCurrent(window); //creates window create context
	//
	////checks if all functions passed is legal
	//if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	//{
	//	glfwDestroyWindow(window);
	//	glfwTerminate();
	//	return -3;
	//}

	////get ogl version and print
	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//std::cout << "GL: " << major << minor << std::endl;


	////function to clear colors
	//glClearColor(0.25f, 0.25f, 0.25f, 1);
	////enable depth
	//glEnable(GL_DEPTH_TEST);

	////create Gizmo
	//aie::Gizmos::create(10000, 10000, 10000, 10000);
	//
	////sets up camera
	////create view size for camera window
	//mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	////create projection window
	//mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	////goes through loop until escape pressed or windows closed
	//while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	//{
	//	//clear buffer color and depth class
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

	//	glfwSwapBuffers(window); //swap buffers
	//	glfwPollEvents(); //poll events
	//}

	//

	////closes gizmo
	//aie::Gizmos::destroy();

	////destroys window afterwards
	//glfwDestroyWindow(window);
	////stops connecting to Graphics card
	//glfwTerminate();

	////delete afterwards
	////std::cout << "Haro!" << testVec2.x << testVec2.y << std::endl;
	////std::cin.get();

	auto* App = new ApplicationEngine();
	App->AppRun("Engine Demo", 1280, 720, false);

	delete App;

	return 0;
}