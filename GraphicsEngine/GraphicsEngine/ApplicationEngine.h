#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include "Shader.h"
#include "Mesh.h"

class ApplicationEngine : public VirtualStage::Application
{
public:
	ApplicationEngine();
	virtual ~ApplicationEngine();

	virtual bool startUp();
	virtual void shutDown();
	virtual void update(float deltaTime);
	virtual void draw();

protected:
	float m_timer;
	FlyCamera* m_FlyCamera;
		
	aie::ShaderProgram	m_shader;
	Mesh	m_quadMesh;
	Mesh	m_quadMeshTriangle;
	glm::mat4	m_quadTransform;
};

