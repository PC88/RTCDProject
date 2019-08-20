#pragma once
#include "Shape.h"
#include <memory>
#include <glm\glm.hpp>
#include <chrono>

class CircleGraphComp;
class CirclePhysicsComp;

using namespace glm;

class Circle : public Shape

{

private:

	std::unique_ptr<CircleGraphComp> graphicComp;
	std::unique_ptr<CirclePhysicsComp> physicsComp;
	bool inUse = false;
	float halfwidth;

	vec2 velocity;
	vec2 acceleration;
	//vec2 position; // this will init to random points with in screen dimensions in the constructor -PC


public:

	Circle(float& r, vec2& vel, vec2& acc);
	virtual ~Circle();

	void Update(float ElapsedDeltaTime, int width, int height);

	void Render(float ElapsedDeltaTime, int width, int height);

	void OnCollide(int type);

	bool InUse();

	int GetType();

	void CheckBounds();
	float GetHalfwidth();
	vec2 GetDirection() const;
	vec2 GetPosition() const;
	vec2 GetDistanceMetric() const;
};

