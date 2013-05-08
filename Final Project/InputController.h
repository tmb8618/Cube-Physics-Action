#pragma once
#include "Includes.h"

class InputController
{

public:
	InputController(void);

	void controlLoop(const double& dt);

	void matrixInputs();

	mat4& getViewMatrix();
	mat4& getProjectionMatrix();
	
	~InputController(void);

private:
	vec3 cameraPos;
	float horizontalAngle;
	float verticalAngle;
	float fieldOfView;
	float speed;
	float mouseSpeed;

	vec3 directionVec;
	vec3 rightVec;
	vec3 upVec;
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

