#pragma once
#include "Camera.h"
#include "ext.hpp"
#include "glfw3.h"


class FlyCamera : public Camera
{
public:
	FlyCamera(GLFWwindow* a_glfwWindow);
	~FlyCamera();

	void update(float deltaTime, GLFWwindow* a_glfwWindow);
	void setSpeed(float inSpeed);

protected:
	float speed;
	vec3 up;
	double m_mouseX;
	double m_mouseY;

	double m_deltaMouseX;
	double m_deltaMouseY;
	mat4 m_worldTransform;
	mat4 rotMat;
	vec4 upp;
};

