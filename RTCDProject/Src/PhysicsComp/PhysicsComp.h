#pragma once
#include <chrono>
#include <glm/glm.hpp>
#include "Transform.h"
#include <memory>

class PhysicsComp
{
public:
	PhysicsComp();
	virtual ~PhysicsComp();

	virtual void Update(float ElapsedDeltaTime, int width, int height) = 0;

	virtual void Move(glm::vec2 translation) = 0;

	virtual void TCVelocityVerletSolver(float ElapsedDeltaTime, int width, int height) = 0;

	virtual glm::vec2 GetPosition() const = 0; // position and direction are here just for debugging, they should have 
	                                     // the same value as shape transform -PC
	virtual glm::vec2 GetDirection() const = 0;

	virtual void ReverseY() = 0;

	virtual void ReverseX() = 0;

};

