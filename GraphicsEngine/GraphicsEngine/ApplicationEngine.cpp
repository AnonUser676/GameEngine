#include "ApplicationEngine.h"



ApplicationEngine::ApplicationEngine()
{
}


ApplicationEngine::~ApplicationEngine()
{
}

bool ApplicationEngine::startUp()
{
	m_FlyCamera = new FlyCamera();

	return true;
}

void ApplicationEngine::shutDown()
{

}

void ApplicationEngine::update(float deltaTime)
{
	m_timer += deltaTime;

	m_FlyCamera->update(deltaTime, window);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void ApplicationEngine::draw()
{
	clearScreen();

	aie::Gizmos::clear();
	//adds 3-axis line 
	aie::Gizmos::addTransform(glm::mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	//for drawing grid
	for (int i = 0; i < 21; i++)
	{
		aie::Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);

		aie::Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	//iniitiate draw with camera set-up by projection and view values
	//aie::Gizmos::draw(projection * view);
}