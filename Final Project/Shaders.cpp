#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "Shaders.h"

/*
	Thank you angel, opengl-tutorial.org, and openglbook.com. You all had different ways
	to do the exact same thing, and not actually fix my problems.
*/

GLuint ShaderStart(const char* vertexFilePath,const char* fragmentFilePath)
{
	/*********************************************************************
	*  READS IN VERTEX SHADER
	*/
	fstream vertexShaderStream(vertexFilePath, std::ios::in);
	string vertexShaderLines;

	if (vertexShaderStream.is_open())
	{
		stringstream buffer;

		buffer << vertexShaderStream.rdbuf();
		//cout << buffer.str() << endl;
		vertexShaderLines = buffer.str();
	}

	
	/*********************************************************************
	*   READS IN FRAGMENT SHADER
	*/

	fstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	string fragmentShaderLines;
	if (fragmentShaderStream.is_open())
	{
		stringstream buffer;

		buffer << fragmentShaderStream.rdbuf();
		//cout << buffer.str() << endl;
		fragmentShaderLines = buffer.str();
	}


	/*********************************************************************
	*   Complies Vertex Shader
	*/

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	char const* vertexShaderPointer = vertexShaderLines.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderPointer, NULL);
	glCompileShader(vertexShader);
	
	GLint compiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		cout << "Vertex Shader Compliation Failed!!";
	}


	/*********************************************************************
	*   Complies Fragment Shader
	*/
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char const* fragmentShaderPointer = fragmentShaderLines.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderPointer, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		cout << "Fragment Shader Compilation Failed!!";
	}
	

	/*********************************************************************
	*  Attaches shaders to final project program, then links GL to the program
	*/
	GLuint ProgramID = glCreateProgram();

	glAttachShader(ProgramID, vertexShader);
	glAttachShader(ProgramID, fragmentShader);

	glLinkProgram(ProgramID);
	glUseProgram(ProgramID);

    return ProgramID;
}