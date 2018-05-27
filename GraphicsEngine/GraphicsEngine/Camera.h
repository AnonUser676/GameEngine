#pragma once
#include <glm.hpp>
#include <glfw3.h>

using glm::mat4;
using glm::vec3;
using glm::vec4;

class Camera
{
public:
	Camera();
	~Camera();

	virtual void update(float deltaTime, GLFWwindow* a_glfwWindow) = 0;
	void setPerspective(const float &fieldOfView,const float &aspectRatio, const float &near, const float &far);
	void setLookAt(const vec3 &from, const vec3 &to, const vec3 &up);
	void setPos(const vec3 &position);
	mat4 getWorldTransform() const;
	mat4 getView() const;
	mat4 getProjection() const;
	mat4 getProjectionView() const;

protected:

	mat4 worldTransform;
	mat4 viewTransform;
	mat4 projectionTransform;
	mat4 projectionViewTransform;

	void updateProjectionViewTransform();
};

