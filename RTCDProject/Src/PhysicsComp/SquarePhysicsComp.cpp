#include "SquarePhysicsComp.h"


SquarePhysicsComp::SquarePhysicsComp(std::shared_ptr<Transform> ShapeTransform, vec2& vel, vec2& acc, float& hw)
	: ShapeTransform(ShapeTransform), acceleration(acc), velocity(vel), m_halfwidth(hw)
	// defined for philosophy not actually implemented in a project of this scale -PC
{
}


SquarePhysicsComp::~SquarePhysicsComp()
{
}

void SquarePhysicsComp::Update(float ElapsedDeltaTime, int width, int height)
{
	TCVelocityVerletSolver(ElapsedDeltaTime, width, height); 
}

void SquarePhysicsComp::Move(glm::vec2 translation)
{
	ShapeTransform->Translate(translation); 
}

inline glm::vec2 operator*(const glm::vec2& v, const long long& m)  // needs to be inline or multiple definitions in translation unit -PC
{
	return glm::vec2(v.x * m, v.y * m);
}

void SquarePhysicsComp::TCVelocityVerletSolver(float ElapsedDeltaTime, int width, int height)
{ 
	Move(ElapsedDeltaTime * velocity + 0.5f * ElapsedDeltaTime * ElapsedDeltaTime * acceleration);
	vec2 velInBetween = velocity + 0.5f * ElapsedDeltaTime * acceleration;
	velocity = velInBetween + 0.5f * acceleration;
}

glm::vec2 SquarePhysicsComp::GetPosition() const
{
	return ShapeTransform->getPosition(); 
}

glm::vec2 SquarePhysicsComp::GetDirection() const
{
	return ShapeTransform->getUpDir(); 
}

void SquarePhysicsComp::ReverseX()
{
	velocity = vec2(-velocity.x, velocity.y);
}

void SquarePhysicsComp::ReverseY()
{
	velocity = vec2(velocity.x, -velocity.y);
}
