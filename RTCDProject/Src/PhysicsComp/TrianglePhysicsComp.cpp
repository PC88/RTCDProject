#include "TrianglePhysicsComp.h"
#include <iostream>

TrianglePhysicsComp::TrianglePhysicsComp(std::shared_ptr<Transform> ShapeTransform, float& hw, glm::vec2& vel, glm::vec2& acc)
	:ShapeTransform(ShapeTransform), halfwidth(hw),
	velocity(vel), acceleration(acc)
{
}


TrianglePhysicsComp::~TrianglePhysicsComp()
{
}

void TrianglePhysicsComp::Update(float ElapsedDeltaTime, int width, int height)
{
	TCVelocityVerletSolver(ElapsedDeltaTime, width, height);
}

void TrianglePhysicsComp::Move(glm::vec2 translation)
{
	//std::cout << translation.x << " " << translation.y << std::endl;
	ShapeTransform->Translate(translation);
}

inline glm::vec2 operator*(const glm::vec2& v, const long long& m) // needs to be inline or multiple definitions in translation unit -PC
{
	return glm::vec2(v.x * m, v.y * m);
}

void TrianglePhysicsComp::TCVelocityVerletSolver(float ElapsedDeltaTime, int width, int height)
{
	Move(ElapsedDeltaTime * velocity + 0.5f * ElapsedDeltaTime * ElapsedDeltaTime * acceleration);
	vec2 velInBetween = velocity + 0.5f * ElapsedDeltaTime * acceleration;
	velocity = velInBetween + 0.5f * acceleration;
}

glm::vec2 TrianglePhysicsComp::GetPosition() const
{
	return ShapeTransform->getPosition();
}

glm::vec2 TrianglePhysicsComp::GetDirection() const
{
	return ShapeTransform->getUpDir();
}

void TrianglePhysicsComp::ReverseX()
{

	velocity = vec2(-velocity.x, velocity.y);
}

void TrianglePhysicsComp::ReverseY()
{
	velocity = vec2(velocity.x, -velocity.y);
}
