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

	setBackGroundColor(0.25f, 0.25f, 0.25f);

	//initialize gizmo primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	//create simple camera transforms
	
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./simple.vert");
	
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./simple.frag");
	
	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		system("pause");
		return false;
	}

	if (m_bunnyMesh.load("./stanford/bunny.obj", true, true) == false)
	{
		printf("Bunny Mesh Error! \n");
		system("pause");
		return false;
	}
		
	m_bunnyTransform =
	{
		90.f,0,0,0,
		0,20.f,0,0,
		0,0,90.f,0,
		0,0,0,1
	};

	if (m_spearMesh.load("./soulspear/soulspear.obj") == false)
	{
		printf("Spear Mesh Error! \n");
		system("pause");
		return false;
	}

	m_spearTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	m_quadMesh.initialiseQuad();

	// define 4 vertices for 2 triangles
	//Mesh::Vertex vertices[4];
	//vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	//vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	//vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	//vertices[3].position = { 0.5f, 0, -0.5f, 1 };
	//unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
	//m_quadMeshTriangle.initialise(4, vertices, 6, indices);
	
	//make the quad 10 units wide
	m_quadTransform =
	{
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};
	
	m_light.diffuse = { 1,1,1 };
	m_light.specular = { 0,.25f,.5f };
	m_ambientLight = { 0.99f,0.99f, 0.99f };

	m_positions[0] = glm::vec3(10, 5, 10);

	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load texture! \n");
		system("pause");
		return false;
	}

	//m_quadCube.addAABB(vec3(3, 2, 1), vec3(1, 1, 1));
	m_quadPyramid.addPyramid(vec3(4, 4, 4), vec3(1, 1, 1));
	return true;
}

void ApplicationEngine::shutDown()
{

}

void ApplicationEngine::update(float deltaTime)
{
	m_timer += deltaTime;

	//query time since application started
	float time = glfwGetTime();

	m_FlyCamera->update(deltaTime, window);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();

	//rotate light
	m_light.direction = glm::normalize(vec3(glm::cos(time * 2), glm::sin(time * 2), 0));
}

void ApplicationEngine::draw()
{
	clearScreen();

	//aie::Gizmos::clear();

	//update perspective in case window resizes
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);

	if (true) 
	{
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
		
		//bind shader
		m_shader.bind();
		
		//bind light
		m_shader.bindUniform("cameraPosition", m_FlyCamera->getPosition());
		m_shader.bindUniform("Ia", m_ambientLight);
		m_shader.bindUniform("Id", m_light.diffuse);
		m_shader.bindUniform("Is", m_light.specular);
		m_shader.bindUniform("LightDirection", m_light.direction);

		//bind transform
		auto pvm = m_FlyCamera->getProjection() * m_FlyCamera->getView() /* m_quadTransform*/;
		m_shader.bindUniform("ProjectionViewModel", pvm);

		m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));

		//bind texture location
		m_shader.bindUniform("diffuseTexture", 0);

		//bind texture to specified location
		m_gridTexture.bind(0);

		//draw quad
		m_quadMesh.draw();
		
		//draw spear
		m_spearMesh.draw();

		//draw quadmesh and bunny
		//m_quadMesh.draw();
		//m_bunnyMesh.draw();

		//m_quadMeshTriangle.draw();

		//m_quadCube.draw();
		m_quadPyramid.draw();
		
		//Iniitiate draw with camera set-up by projection and view values
		//aie::Gizmos::draw(m_FlyCamera->getProjection() * m_FlyCamera->getView());
		
		//draw 3d Gizmos
		aie::Gizmos::draw(m_FlyCamera->getProjectionView());

		//draw2d Gizmos
		//aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());

	}
	
}