//TYLER BROGNA

#pragma once
#include "Includes.h"
#include "Cube.h"
#include "InputController.h"

Cube::Cube(void)
{
	length = 1;
	height = 1;
	depth = 1;

	current.position = vec3(2, 0, 0);
	current.linMomentum = vec3(0, 0, -10);
	current.angMomentum = vec3(0, 0, 0);
	current.orientation = quat(1, 0, 0, 0);
	current.shearAmount = vec3(.5,0,0);
	current.size = vec3(1, 1, 1);
	current.mass = 1.0f;
	current.inverseMass = 1.0f / current.mass;
	current.inertia = mat3(1.0f / 12.0f * current.mass * (height * height + depth * depth), 0, 0,
							0, 1.0f / 12.0f * current.mass * (length * length + depth * depth), 0,
							0, 0, 1.0f / 12.0f * current.mass * (length * length + height * height)); 
	current.inverseInertia = glm::inverse(current.inertia);


	current.recalculate();
	previous = current;

	//srand(time(NULL));
}

//THIS IS FOR YOU, gafferongames!!
//thank you for basically doing RK4 for me, and helping me understand 
// all the bizzare inbetweens of this.

Cube::State Cube::interpolate(const State& before, const State& now, float alpha)
{
	State s = now;
	s.position = before.position * (1 - alpha) + now.position * alpha;
	s.linMomentum = before.linMomentum * ( 1 - alpha) + now.linMomentum * alpha;
	s.orientation = glm::mix(before.orientation, now.orientation, alpha);
	s.angMomentum = before.angMomentum * (1 - alpha) + now.angMomentum * alpha;
	s.recalculate();
	return s;
}

void Cube::intergrate(State& state, float t, float dt)
{
	Derivative a = evaluate(state, 0);
	//cout << "A: " << a.velocity.x << ", " << a.velocity.y << ", " << a.velocity.z << endl;
	Derivative b = evaluate(state, 0, dt * 0.5f, a);
	//cout << "B: " << b.velocity.x << ", " << b.velocity.y << ", " << b.velocity.z << endl;
	Derivative c = evaluate(state, 0, dt * 0.5f, b);
	//cout << "C: " << c.velocity.x << ", " << c.velocity.y << ", " << c.velocity.z << endl;
	Derivative d = evaluate(state, 0, dt, c);
	//cout << "D: " << d.velocity.x << ", " << d.velocity.y << ", " << d.velocity.z << endl;

	state.position += 1.0f/6.0f * dt * 
						(a.velocity + 2.0f * (b.velocity + c.velocity) + d.velocity);

	state.linMomentum += 1.0f / 6.0f * dt *
						(a.force + 2.0f * (b.force + c.force) + d.force);

	state.orientation = state.orientation + (1.0f / 6.0f * dt *
											(a.spin + 2.0f * (b.spin + c.spin) + d.spin));

	state.angMomentum += 1.0f / 6.0f * dt *
						(a.torque + 2.0f * (b.torque + c.torque) + d.torque);

	state.recalculate();
}

/*
	THE OTHER EVALUATE. this is for the first derivation only. at time t, which is the time 0.
*/

Cube::Derivative Cube::evaluate(const State& state, float time)
{
	Derivative out;
	out.velocity = state.velocity;
	out.spin = state.spin;
	forces(state, time, out.force, out.torque);
	return out;
}

/*
	TWO EVALUATE METHODS. One is the regualar one, done for b, c and d.
	This multiplies the changed state by the cumulative velocities from the derivatives
	which is time 0 + dt.
*/
Cube::Derivative Cube::evaluate(State initial, float time, float dt, const Derivative& d)
{
	initial.position += d.velocity * dt;
	initial.linMomentum += d.force * dt;
	initial.orientation = initial.orientation + (d.spin * dt);
	initial.angMomentum += d.torque * dt;

	initial.recalculate();

	Derivative out;
	out.velocity = initial.velocity;
	out.spin = initial.spin;
	forces(initial, dt, out.force, out.torque);
	return out;
}

void Cube::forces(const State& state, float t, vec3& force, vec3& torque)
{
	force = -5.0f * state.position;

	torque.x = 10.0f;

	torque -= state.angVelocity * 0.2f;

	// attract towards origin

	//force = -1.0f * state.position;
	
	// sine force to add some randomness to the motion

	force.x += ((float)(rand() % 100) / 50) * glm::sin(t*0.9f + 0.5f);
	force.y += ((float)(rand() % 100) / 50) * glm::sin(t*0.5f + 0.4f);
	force.z += ((float)(rand() % 100) / 50) * glm::sin(t*0.7f + 0.9f);

	// sine torque to get some spinning action

	torque.x = 1.0 * glm::sin(t*0.9f + 0.5f);
	torque.y = 1.1f * glm::sin(t*0.5f + 0.4f);
	torque.z = 1.2f * glm::sin(t*0.7f + 0.9f);

	// damping torque so we dont spin too fast

	torque -= 0.2f * state.angVelocity;
}

void Cube::update(const double time, const double dt)
{
	previous = current;
	intergrate(current, time, dt);
}

mat4 Cube::makeModel()
{
	//mat4 identity = mat4(1);
	//mat4 shear = mat4(1,current.shearAmount.x, current.shearAmount.x,0,current.shearAmount.y,1,current.shearAmount.y,0,current.shearAmount.z,current.shearAmount.z,1,0,0,0,0,1);
	mat4 trans = glm::translate(current.position.x, current.position.y, current.position.z); //make a matrix for the position in the world
	mat4 scale = glm::scale(current.size.x, current.size.y, current.size.z); //size.
	mat4 rotate = glm::toMat4(current.orientation); //rotation. a quaterion to matrix 4

	mat4 modelMatrix =  trans * rotate * scale; //multiplying all together gives the position, scale, and rotation relative to origin

	return modelMatrix;
}


	//vectors representing the position of the 8 vertices of the cube
	//vec3 botLeftFront = vec3(position.x - halfLength, position.y - halfHeight, position.z + halfDepth);
	//vec3 botRightFront = vec3(position.x + halfLength, position.y - halfHeight, position.z + halfDepth);
	//vec3 topLeftFront = vec3(position.x - halfLength, position.y + halfHeight, position.z + halfDepth);
	//vec3 topRightFront = vec3(position.x + halfLength, position.y + halfHeight, position.z + halfDepth);
	
	//vec3 botLeftBack = vec3(position.x - halfLength, position.y - halfHeight, position.z - halfDepth);
	//vec3 botRightBack = vec3(position.x + halfLength, position.y - halfHeight, position.z - halfDepth);
	//vec3 topLeftBack = vec3(position.x - halfLength, position.y + halfHeight, position.z - halfDepth);
	//vec3 topRightBack = vec3(position.x + halfLength, position.y + halfHeight, position.z - halfDepth);

	//    v6----- v7
	//   /|      /|
	//  v2------v3|
	//  | |     | |
	//  | |v4---|-|v5
	//  |/      |/
	//  v0------v1
	//	
	//	Sweet cube graphic made by: Song Ho Ahn [www.songho.ca/opengl/gl_vbo.html]
	//	Also, Song helped a lot with my understanding of VBO. Thanks!

Cube::~Cube(void)
{

}
