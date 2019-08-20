#pragma once
#include "PhysicsComp.h"


class CirclePhysicsComp :
	public PhysicsComp
{
public:
	CirclePhysicsComp(std::shared_ptr<Transform> ShapeTransform, float& r, glm::vec2& vel, glm::vec2& acc);
	virtual ~CirclePhysicsComp();

	void Update(float ElapsedDeltaTime, int width, int height);

	void Move(glm::vec2 translation);

	void TCVelocityVerletSolver(float ElapsedDeltaTime, int width, int height);

	glm::vec2 GetPosition() const; // position and direction are here just for debugging, 
									  // they should have the same value as shape transform -PC
	glm::vec2 GetDirection() const;

	void ReverseX();

	void ReverseY();
private:

	std::shared_ptr<Transform> ShapeTransform;
	float radius;
	glm::vec2 velocity;
	glm::vec2 acceleration;


};

