#pragma once
#include "Includes.h"
#include "InputController.h"


InputController::InputController(void)
{
	cameraPos = vec3(2, .7, 6);
	horizontalAngle = 26.755024;
	verticalAngle = -19.055010;
	fieldOfView = 45.0f;
	speed = 5.0f;
	mouseSpeed = .005f;
}

void InputController::controlLoop(const double& dt) //traslate * rotate * scale * original
{
	int xPos;
	int yPos;

	glfwGetMousePos(&xPos, &yPos); //current mouse position on the window
	glfwSetMousePos(1280 / 2, 720 / 2);

	horizontalAngle += mouseSpeed * float((1280 / 2) - xPos); //change the two angles of the camera
	verticalAngle += mouseSpeed * float((720 / 2) - yPos);  //right does not move.
	
	directionVec = vec3(cos(verticalAngle) * sin(horizontalAngle),
						sin(verticalAngle),
						cos(verticalAngle) * cos(horizontalAngle)); //where the camera is pointing, forwards

	rightVec = vec3(sin(horizontalAngle - 3.14f/2.0f),
					0,
					cos(horizontalAngle - 3.14f/2.0f)); // the right of the camera. always static.

	upVec = vec3(cross(rightVec, directionVec)); //up of the camera, which is perpendicualr to the
															//plane formed by the right and direction
	float dtFloat = static_cast<float>(dt);

	if (glfwGetKey('W') == GLFW_PRESS) //forward
	{
		cameraPos += directionVec * dtFloat * speed;
	}

	if (glfwGetKey('A') == GLFW_PRESS) //strafe left
	{
		cameraPos -= rightVec * dtFloat * speed;
	}

	if (glfwGetKey('S') == GLFW_PRESS) //backward
	{
		cameraPos -= directionVec * dtFloat * speed;
	}

	if (glfwGetKey('D') == GLFW_PRESS) //strafe right
	{
		cameraPos += rightVec * dtFloat * speed;
	}

	if (glfwGetKey('C') == GLFW_PRESS) //strafe right
	{
		cameraPos -= upVec * dtFloat * speed;
	}

	if (glfwGetKey('Q') == GLFW_PRESS) //strafe right
	{
		cameraPos += upVec * dtFloat * speed;
	}
	
	//View matrix. Where the camera is looking, expressed as a matrix
	viewMatrix = lookAt(cameraPos,
						cameraPos + directionVec,
						upVec);
	
	//projection matrix. the computed field of view of the camera. at an angle, 16/9 perspective, and within a bounds
	projectionMatrix = perspective(fieldOfView, 16.0f / 9.0f, .1f, 100.0f);
}

mat4& InputController::getViewMatrix()
{
	return viewMatrix;
}

mat4& InputController::getProjectionMatrix()
{
	return projectionMatrix;
}

InputController::~InputController(void)
{

}
