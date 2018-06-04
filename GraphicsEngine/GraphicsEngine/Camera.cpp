#include "Camera.h"
#include <ext.hpp>


Camera::Camera()
{
	//sets up camera
	
	worldTransform = mat4(0);
	viewTransform = mat4(0);
	projectionTransform = mat4(0);
	projectionViewTransform = mat4(0);
	
	//create view size for camera window
	setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	//create projection window
	setPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
}


Camera::~Camera()
{
}

void Camera::updateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}

void Camera::setPerspective(const float &fieldOfView, const float &aspectRatio, const float &near, const float &far)
{
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, near, far);
	updateProjectionViewTransform();
}

void Camera::setLookAt(const vec3 &from, const vec3 &to, const vec3 &up)
{
	viewTransform = glm::lookAt(from, to, up);
}

void Camera::setPos(const vec3 &position)
{
	worldTransform[3] = glm::vec4(position, worldTransform[3][3]);
	updateProjectionViewTransform();
}

mat4 Camera::getWorldTransform() const
{
	return worldTransform;
}

vec3 Camera::getPosition() const
{
	return vec3(worldTransform[3][0], worldTransform[3][1], worldTransform[3][2] );
}

mat4 Camera::getView() const
{
	return viewTransform;
}

mat4 Camera::getProjection() const
{
	return projectionTransform;
}

mat4 Camera::getProjectionView() const
{
	return projectionViewTransform;
}