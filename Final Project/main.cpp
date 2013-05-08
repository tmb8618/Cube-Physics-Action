#pragma once
#include "Includes.h"

#include "InputController.h"
#include "Shaders.h"
#include "Cube.h"
//#include "Physics.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define scale 1


GLuint programID;
GLuint MatrixID;
double lastTime = 0;
double currentTime = 0;
double dt = 0;

bool paused = false;
//bool startscreen = true;
//bool mesh = false;
//bool prevmesh = false;


#pragma region 

GLfloat ctrlpoints[4][4][3] = {
   {{-2.0*scale, -1.5*scale, 3.0*scale}, {-1.5*scale, -1.5*scale, 2.5*scale}, {0.5*scale, -1.5*scale, -2.0*scale}, {2.5*scale, -1.5*scale, 1.5*scale}}, 
   {{-1.5*scale, -0.5*scale, 1.0*scale}, {-1.0*scale, -0.5*scale, 2.5*scale}, {1.0*scale, -0.5*scale, 0.5*scale}, {1.5*scale, -0.5*scale, -1.5*scale}}, 
   {{-2.5*scale, 0.5*scale, 3.5*scale}, {-0.5*scale, 0.5*scale, 0.0*scale}, {1.0*scale, 0.5*scale, 3.5*scale}, {1.5*scale, 0.5*scale, 4.0*scale}}, 
   {{-1.5*scale, 1.5*scale, -3.0*scale}, {0.5*scale, 1.5*scale, -1.5*scale}, {1.5*scale, 1.5*scale, 0.5*scale}, {1.5*scale, 1.5*scale, -2.0*scale}}
};


const GLfloat cubeVertices[]= { .5f, .5f, .5f,  -.5f, .5f, .5f,  -.5f,-.5f, .5f,      // v0-v.5f-v2 (front)
								-.5f,-.5f, .5f,   .5f,-.5f, .5f,   .5f, .5f, .5f,      // v2-v3-v0

								.5f, .5f, .5f,   .5f,-.5f, .5f,   .5f,-.5f,-.5f,      // v0-v3-v4 (right)
								.5f,-.5f,-.5f,   .5f, .5f,-.5f,   .5f, .5f, .5f,      // v4-v5-v0

								.5f, .5f, .5f,   .5f, .5f,-.5f,  -.5f, .5f,-.5f,      // v0-v5-v6 (top)
								-.5f, .5f,-.5f,  -.5f, .5f, .5f,   .5f, .5f, .5f,      // v6-v.5f-v0

								-.5f, .5f, .5f,  -.5f, .5f,-.5f,  -.5f,-.5f,-.5f,      // v.5f-v6-v7 (left)
								-.5f,-.5f,-.5f,  -.5f,-.5f, .5f,  -.5f, .5f, .5f,      // v7-v2-v.5f

								-.5f,-.5f,-.5f,   .5f,-.5f,-.5f,   .5f,-.5f, .5f,      // v7-v4-v3 (bottom)
								.5f,-.5f, .5f,  -.5f,-.5f, .5f,  -.5f,-.5f,-.5f,      // v3-v2-v7

								.5f,-.5f,-.5f,  -.5f,-.5f,-.5f,  -.5f, .5f,-.5f,      // v4-v7-v6 (back)
								-.5f, .5f,-.5f,   .5f, .5f,-.5f,   .5f,-.5f,-.5f,		// v6-v5-v4
		

								5, 5, 5,	-5, -5, -5,

								5, 5, -5,	-5, -5, 5,

								-5, 5, 5,	5, -5, -5

								-5, 5, -5,	5, -5, 5};

const GLfloat cubeNormals[] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
								0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

								1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
								1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

								0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
								0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

								-1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
								-1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

								0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
								0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

								0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
								0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

//THANKS opengl-tutorial.org for allowing me to copy paste the colors
const GLfloat cubeColors[] = {0.583f,  0.771f,  0.014f,
								0.609f,  0.115f,  0.436f,
								0.327f,  0.483f,  0.844f,
								0.822f,  0.569f,  0.201f,
								0.435f,  0.602f,  0.223f,
								0.310f,  0.747f,  0.185f,
								0.597f,  0.770f,  0.761f,
								0.559f,  0.436f,  0.730f,
								0.359f,  0.583f,  0.152f,
								0.483f,  0.596f,  0.789f,
								0.559f,  0.861f,  0.639f,
								0.195f,  0.548f,  0.859f,
								0.014f,  0.184f,  0.576f,
								0.771f,  0.328f,  0.970f,
								0.406f,  0.615f,  0.116f,
								0.676f,  0.977f,  0.133f,
								0.971f,  0.572f,  0.833f,
								0.140f,  0.616f,  0.489f,
								0.997f,  0.513f,  0.064f,
								0.945f,  0.719f,  0.592f,
								0.543f,  0.021f,  0.978f,
								0.279f,  0.317f,  0.505f,
								0.167f,  0.620f,  0.077f,
								0.347f,  0.857f,  0.137f,
								0.055f,  0.953f,  0.042f,
								0.714f,  0.505f,  0.345f,
								0.783f,  0.290f,  0.734f,
								0.722f,  0.645f,  0.174f,
								0.302f,  0.455f,  0.848f,
								0.225f,  0.587f,  0.040f,
								0.517f,  0.713f,  0.338f,
								0.053f,  0.959f,  0.120f,
								0.393f,  0.621f,  0.362f,
								0.673f,  0.211f,  0.457f,
								0.820f,  0.883f,  0.371f,
								0.982f,  0.099f,  0.879f};

#pragma endregion points for shapes

const GLfloat tri[] = { -1.0f, -1.0f, 0.0f,
						  1.0f, -1.0f, 0.0f,
						  0.0f,  1.0f, 0.0f};

GLuint vaoID;
GLuint vertexBuffer;
GLuint normalBuffer;
GLuint colorBuffer;

void initalize()
{
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);

	//double check everything is running smooth. 
	if (!glfwInit())
	{
		cout << "GLFW IS AN ABUSIVE FATHER" << endl;
	}

	glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

	glewExperimental = true;
	if (!glewInit())
	{
		cout << "JEGUS WHY ISNT GLEW WORKING" << endl;
	}
	
	//cout << GetCurrentDirectory();
	programID = ShaderStart("Shaders\\Transform.vertex", "Shaders\\White.fragment");

	glfwSetWindowTitle("Cube Land");
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	MatrixID = glGetUniformLocation(programID, "MVP");
}

void mainLoop()
{
	glfwEnable( GLFW_STICKY_KEYS );
	InputController input;			//Camera controller class.
	Cube cube;			//FOR
	Cube testCube;		//TESTING
	mat4 identityMat = mat4(1.0);	//would be useful to have this onhand for now. Change later for efficiency?
	mat4 MVP;		//also on hand for ease of access. Model * view * projection

	glGenVertexArrays(1, &vaoID); //VAO. Holds the buffers.
	glBindVertexArray(vaoID);	//Vao location holder

	glGenBuffers(1, &vertexBuffer);		//Buffer object for the points of cube
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //Bind buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);	//what data does the buffer hold
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,	(void*)0); //???
	glEnableVertexAttribArray(0); //Turn it on!

	glGenBuffers(1, &colorBuffer);		//Buffer object for the colors
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3,	GL_FLOAT, GL_FALSE,	0, (void*)0);
	glEnableVertexAttribArray(1);
	
	glGenBuffers(1, &normalBuffer);		//Buffers for the normals
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	float accum = 0.0f;
	float t = 0.0f;

	do
	{
		currentTime = glfwGetTime(); //dt calc for physics
		dt = currentTime - lastTime;
		lastTime = currentTime;

		if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			paused = !paused; //switches pause state when space is pressed
		}

		glClear(GL_COLOR_BUFFER_BIT); //Makes the background bluish.

		if (!paused)
		{
			testCube.update(currentTime, dt);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 0, 0); // DONT TOUCH THIS

		glMatrixMode(GL_MODELVIEW);
		

		//if(startscreen == false)
		//{

			glBegin(GL_LINES); //These lines are so i can see where the origin is. Make sure all my cubes are in the right spot
				//glColor4f(1.0, 1.0, 0.0, 1.0);
				glVertex4f(.5, .5, .5, 0.0);
				//glColor4f(1.0, 1.0, 0.0, 1.0);
				glVertex4f(-.5, -.5, -.5, 0.0);

				//glColor4f(1.0, 0.0, 0.0, 1.0);
				glVertex4f(.5, .5, -.5, 0.0);
				//glColor4f(1.0, 0.0, 0.0, 1.0);
				glVertex4f(-.5, -.5, .5, 0.0);

				//glColor4f(1.0, 0.0, 0.0, 1.0);
				glVertex4f(-.5, .5, .5, 0.0);
				//glColor4f(1.0, 0.0, 0.0, 1.0);
				glVertex4f(.5, -.5, -.5, 0.0);

				//glColor4f(1.0, 0.0, 0.0, 1.0);
				glVertex4f(-.5, .5, -.5, 0.0);
				//glColor4f(1.0, 0.0, 0.0, 1.0);
				glVertex4f(.5, -.5, .5, 0.0);
			glEnd();


			glBegin(GL_LINES); //Draws a line from the center of basic cube to test cube. Make sure the renders match up to the numbers
				glVertex3f(testCube.current.position.x, testCube.current.position.y, testCube.current.position.z);
				glVertex3f(0,0,0);
			glEnd();

			input.controlLoop(dt); //camera loop
		
			mat4 projectionMat = input.getProjectionMatrix(); //projection matrix calculated in camera controller
			mat4 viewMat = input.getViewMatrix(); //also from camera controller
		
			glBindVertexArray(vaoID); //Uhhh...start the vao again?
		
			/*MVP = projectionMat * viewMat * cube.update(currentTime, dt); //MVP matrix. cumulative total of how cube is drawn
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]); //send to GLSL, the vertex Shader
			glDrawArrays(GL_TRIANGLES, 0, 36); //Draw a cube*/
		
			MVP = projectionMat * viewMat * testCube.makeModel();
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			MVP = projectionMat * viewMat * mat4(1.0);
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			glBindVertexArray(0);
		/*}
		else
		{

			//If mesh is on, draw the mesh only
			/*if(mesh == true)
			{
				//With help from a helpful user on stackoverflow.com
				for(int j = 0; j <=8; j++){
					glBegin(GL_LINE_STRIP);
					for(int i = 0; i <= 30; i++)
						glEvalCoord2f((GLfloat)i/30, (GLfloat)j/8);
					glEnd();
					glBegin(GL_LINE_STRIP);
					for (int i = 0; i <=30; i ++)
						glEvalCoord2f((GLfloat)j/8, (GLfloat)i/30);
					glEnd();
				}
			}
			//otherwise draw the surface
			else
			{
				glEvalMesh2(GL_FILL, 0, 20, 0, 20);
			}
			//If f is pressed once, change the mesh mode
			if(glfwGetKey('F') == GLFW_PRESS && prevmesh == mesh)
			{
				if(mesh)
					mesh = false;
				else
					mesh = true;
			}
			if(glfwGetKey('F') == GLFW_RELEASE)
			{
				prevmesh = mesh;
			}
			//If b pressed, advance past start screen
			if(glfwGetKey('B') == GLFW_PRESS)
				startscreen = false;
				
			input.controlLoop(dt); //camera loop
			mat4 projectionMat = input.getProjectionMatrix(); //projection matrix calculated in camera controller
			mat4 viewMat = input.getViewMatrix(); //also from camera controller
			glBindVertexArray(vaoID); //Uhhh...start the vao again?
			MVP = projectionMat * viewMat * mat4(1.0);
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

			glBindVertexArray(0);
		}*/

		glfwSwapBuffers(); //Swap buffers, display everything calculated

		
	}
	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS);

	cout << "HNNNGH" << endl;
}

void init()
{
	//set up the bezier map
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	//cout << "Press B to advance to main simulation." << endl;
	//cout << "Press F to change the Bezier surface from mesh to solid and back." << endl;
	cout << "Use Mouse to look around." << endl;
	cout << "Use WASD to move the camera." << endl;
}

void main()
{
	initalize();
	init();
	glClearColor(0.0, 0.2, 0.8, 1.0);

	mainLoop();
}