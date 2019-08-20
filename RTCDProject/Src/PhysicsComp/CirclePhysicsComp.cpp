#include "CirclePhysicsComp.h"


CirclePhysicsComp::CirclePhysicsComp(std::shared_ptr<Transform> ShapeTransform, float& r, glm::vec2& vel, glm::vec2& acc)
	:ShapeTransform(ShapeTransform), radius(r), velocity(vel), acceleration(acc)
{
}


CirclePhysicsComp::~CirclePhysicsComp()
{
}

void CirclePhysicsComp::Update(float ElapsedDeltaTime, int width, int height)
{
	TCVelocityVerletSolver(ElapsedDeltaTime, width, height);
}

void CirclePhysicsComp::Move(glm::vec2 translation)
{
	ShapeTransform->Translate(translation);
}

inline glm::vec2 operator*(const glm::vec2& v, const long long& m) // needs to be inline or multiple definitions in translation unit -PC
{
	return glm::vec2(v.x * m, v.y * m);
}

void CirclePhysicsComp::TCVelocityVerletSolver(float ElapsedDeltaTime, int width, int height)
{
	Move(ElapsedDeltaTime * velocity + 0.5f * ElapsedDeltaTime * ElapsedDeltaTime * acceleration);
	vec2 velInBetween = velocity + 0.5f * ElapsedDeltaTime * acceleration;
	velocity = velInBetween + 0.5f * acceleration;
}

glm::vec2 CirclePhysicsComp::GetPosition() const
{
	return ShapeTransform->getPosition();
}

glm::vec2 CirclePhysicsComp::GetDirection() const
{
	return ShapeTransform->getUpDir();
}

void CirclePhysicsComp::ReverseX()
{
	velocity = vec2(-velocity.x, velocity.y);
}

void CirclePhysicsComp::ReverseY()
{
	velocity = vec2(velocity.x, -velocity.y);
}

