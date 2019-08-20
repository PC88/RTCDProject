#pragma once
#include <iostream>
#include <glm\glm.hpp>
#include <chrono>
#include "Shape.h"
#include <GL/glut.h>

class TriangleGraphComp;
class TrianglePhysicsComp;
class Transform;
using namespace glm;

class Triangle : public Shape
{
private:

	bool inUse;
	float halfwidth;
	glm::vec2 topPoint;
	glm::vec2 leftPoint;
	glm::vec2 rightPoint;
	//vec2 position;

	vec2 velocity;
	vec2 acceleration;
	
	std::unique_ptr<TriangleGraphComp> graphicComp;
	std::unique_ptr<TrianglePhysicsComp> physicsComp;

public:

	virtual ~Triangle();
	Triangle(float& hw, vec2& vel, vec2& acc);

	void Update(float ElapsedDeltaTime, int width, int height);
	void OnCollide(int type);
	void CheckBounds();
	void Render(float ElapsedDeltaTime, int width, int height);
	vec2 GetDirection() const;
	vec2 GetPosition() const;
	vec2 GetDistanceMetric() const;
	int GetType();
	bool InUse();
	float GetHalfwidth();
	glm::vec2 GetTopPoint();
	glm::vec2 GetLeftPoint();
	glm::vec2 GetRightPoint();
};