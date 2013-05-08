#pragma once
#include "Includes.h"

#include "kdNode.h"

using namespace std;


kdNode::kdNode(int xOrigin, int yOrigin, int zOrigin, int xMax, int yMax, int zMax)
{
	origin.x = xOrigin;
	origin.y = yOrigin;
	origin.z = zOrigin;

	diagonal.x = xMax;
	diagonal.y = yMax;
	diagonal.z = zMax;
}

/*vector<vec3> quickSortSimple(vector<vec3> arr)
{

}*/


void createTree(vector<vec3> points, int numPoints, kdNode* root, int depth = 0)
{
	if (points.size() == 1)
	{

	}

	int splitAxis = 2; // 1 = X axis || 2 = Y axis || 3 = Z axis
	if (root->diagonal.x - root->origin.x > root->diagonal.y - root->origin.y)
	{
		splitAxis = 0;
	}
	else if (root->diagonal.y - root->origin.y > root->diagonal.z - root->origin.z)
	{
		splitAxis = 1;
	}

	//quickSortSimple(points);
	int median = points.size() / 2;

	if (splitAxis == 0) //separate on x axis. This is so bad. I dont know what im doing
	{
		root->left = new kdNode(root->origin.x, root->origin.y, root->origin.z,
								points[median].x, root->diagonal.y, root->diagonal.z);

		root->right = new kdNode(points[median].x, root->origin.y, root->origin.z,
								root->diagonal.x, root->diagonal.y, root->diagonal.z);
	}
	else if (splitAxis == 1) //separate on y axis
	{

	}
	else // separate on z axis
	{

	}

	//createTree(points
}


kdNode::~kdNode(void)
{
	if (left != NULL)
	{
		delete left;
	}
	if (right != NULL)
	{
		delete right;
	}	
}
