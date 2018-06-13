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

	aie::OBJMesh* obj;
	glm::mat4*	m_objTransform;

	//aie::OBJMesh m_spearMesh;
	//glm::mat4 m_spearTransform;

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float power;
	};

	Light m_light;
	glm::vec3 m_ambientLight;
};

