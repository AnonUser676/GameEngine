#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"


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
	
	aie::Texture m_gridTexture;

	aie::ShaderProgram	m_shader;
	Mesh	m_quadMesh;
	Mesh	m_quadMeshTriangle;
	Mesh	m_quadCube;
	Mesh	m_quadPyramid;
	glm::mat4	m_quadTransform;

	aie::OBJMesh m_bunnyMesh;
	glm::mat4	m_bunnyTransform;
};

