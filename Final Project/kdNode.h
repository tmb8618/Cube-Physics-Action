#pragma once
#include "Includes.h"
#include "Cube.h"

using namespace glm;
using namespace std;

class kdNode
{
public:	

	vec3 origin;
	vec3 diagonal;

	kdNode* left;
	kdNode* right;
	int splitType;
	float splitValue;

	kdNode(int xOrigin, int yOrigin, int zOrigin, int xMax, int yMax, int zMax);

	vector<glm::vec3> quickSortSimple(vector<glm::vec3> arr);

	void createTree(vector<vec3> points, int numPoints, kdNode* root, int recursionDepth = 0);

	//void kdInsert();

	void checkPotentialCubes();
	void checkPotentialWalls();
	void createAABBs();

	~kdNode(void);
};

