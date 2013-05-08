#pragma once
#include "Includes.h"

class Physics
{
public:
	Physics(void);



	/*LinearDerive evaluate(const LinearState& initial, float time, float dt, const LinearDerive& d);
	AngularDerive evaluate(const AngularState& initial, float time, float dt, const AngularDerive& d);
	vec3 accelerate(const LinearState& state, float t);
	vec3 alphazie(const AngularState& state, float t);*/

	void calcSystemMomentum();
	
	~Physics(void);
};

