#pragma once
#include "PhysicsComp.h"

class SquarePhysicsComp :
	protected PhysicsComp
{
public:
	SquarePhysicsComp(std::shared_ptr<Transform> ShapeTransform, vec2& vel, vec2& acc, float& hw);

	virtual ~SquarePhysicsComp();

	void Update(float ElapsedDeltaTime, int width, int height) ;

	void Move(glm::vec2 translation);

	void TCVelocityVerletSolver(float ElapsedDeltaTime, int width, int height);

	glm::vec2 GetPosition() const; // position and direction are here just for debugging, 
	                               // they should have the same value as shape transform -PC
	glm::vec2 GetDirection() const;

	void ReverseX();

	void ReverseY();

private:

	float m_halfwidth;
	std::shared_ptr<Transform> ShapeTransform;
	glm::vec2 velocity;
	glm::vec2 acceleration;
};

