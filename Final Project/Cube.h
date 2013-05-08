#pragma once
#include "Includes.h"
#include "Physics.h"

class Cube : Physics
{
public:

	Cube(void);			//default constructor, sets the cubeSize of the cube to a default of 10
	Cube(int cube);
	Cube(int l, int h, int d);		//constructor, sets the cubeSize to size and color values to red, green, blue
	~Cube(void);


	/*
		State struct, done becasue gaffer on games says so. 
		That guy's really smart, and I thank him for this.
	*/
	struct State
	{
		//primary values
		vec3 position;
		vec3 linMomentum;
		quat orientation;
		vec3 angMomentum;
		vec3 shearAmount;

		//secondary values
		vec3 velocity;
		quat spin;
		vec3 angVelocity;

		//constatnt
		float mass;
		float inverseMass;
		mat3 inertia;
		mat3 inverseInertia;
		
		vec3 size;

		void recalculate()
		{
			velocity = linMomentum * inverseMass;

			angVelocity = angMomentum * inverseInertia;
			glm::normalize(orientation);
			spin = 0.5f * quat(0, angVelocity.x, angVelocity.y, angVelocity.z) * orientation;
		}
	};

	struct Derivative
	{
		vec3 velocity;
		vec3 force;
		
		quat spin;
		vec3 torque;
	};
	

	int length;		//half the length of a side of the cube
	//int halfLength;
	int height;
	//int halfHeight;
	int depth;
	//int halfDepth;

	bool isRigidBody;
	bool COMFixed;
	bool immobile;
	float push;

	State current;
	State previous;
	
	vec3 theta;
	vec3 COM;

	bool isColliding;
	Cube* crash;

	//void addForceCalcTorque(float f); //NEED COLLISION DETECTION
	void update(const double time, const double dt);	//recalculates position of cube
	void forces(const State& state, float t, vec3& force, vec3& torque);	//add forces from collision detection
	mat4 makeModel();

private:

	void intergrate(State& state, float t, float dt);	//RK4 intergation method
	Derivative evaluate(const State& state, float t);
	Derivative evaluate(State initial, float time, float dt, const Derivative& d);	//RK4 evalution method for 
	State interpolate(const State& before, const State& now, float alpha = 1.0f);
	

	//proper matrix multiplcation:
	//translation * rotation * scaling
};