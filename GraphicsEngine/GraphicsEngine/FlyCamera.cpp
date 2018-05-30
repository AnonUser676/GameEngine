#include "FlyCamera.h"



FlyCamera::FlyCamera()
{
	speed = 30;
	up = vec3(0);
	m_mouseX = 0;
	m_mouseY = 0;

	m_deltaMouseX = 0;
	m_deltaMouseY = 0;
	worldTransform = mat4(1);
	rotMat = mat4(0);
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float deltaTime, GLFWwindow* a_glfwWindow)
{
	glfwGetCursorPos(a_glfwWindow, &m_mouseX, &m_mouseY);

	m_deltaMouseX = (640 - m_mouseX) * 0.0174533;
	m_deltaMouseY = (360 - m_mouseY) * 0.0174533;

	glfwSetCursorPos(a_glfwWindow, 640, 360);

	upp = glm::inverse(m_worldTransform) * vec4(0, 1, 0, 0);
	
	rotMat = glm::rotate((float)-m_deltaMouseX * deltaTime, vec3(upp[0], upp[1], upp[2]));
	viewTransform = rotMat * viewTransform;
	rotMat = rotate((float)-m_deltaMouseY * deltaTime, vec3(1,0,0));
	viewTransform = rotMat * viewTransform;
	worldTransform = glm::inverse(viewTransform);

	//keyboard stuff

	if (glfwGetKey(a_glfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[0] * deltaTime * -speed;
	}
	if (glfwGetKey(a_glfwWindow, GLFW_KEY_UP) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[2] * deltaTime * -speed;
	}
	if (glfwGetKey(a_glfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[0] * deltaTime * speed;
	}
	if (glfwGetKey(a_glfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		worldTransform[3] += worldTransform[2] * deltaTime * speed;
	}

	viewTransform = glm::inverse(worldTransform);
	updateProjectionViewTransform();
}

void FlyCamera::setSpeed(float inSpeed)
{
	speed = inSpeed;
}