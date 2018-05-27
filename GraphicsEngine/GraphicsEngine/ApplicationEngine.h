#pragma once
#include "Application.h"
#include "FlyCamera.h"

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
};

