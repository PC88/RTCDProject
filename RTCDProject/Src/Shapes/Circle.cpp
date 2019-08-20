#include "Circle.h"
#include <glm\glm.hpp>
#include <chrono>
#include "Transform.h"
#include "CircleGraphComp.h"
#include "CirclePhysicsComp.h"
#include <iostream>

using namespace glm;

Circle::Circle(float& r, vec2& vel, vec2& acc)
	: velocity(vel), acceleration(acc), halfwidth(r)
{
	float initX = std::rand() % (1000 - 1); // make initial position between screen limits does hard code at the moment -PC
	float initY = std::rand() % (1000 - 1);

	Creator = TypeOfCreatedObject::circle; // define meta data -PC

	ShapeTransform = std::make_shared<Transform>();
	position = vec2(initX, initY); // init to random -PC // this actually has to be set in the transform -PC
	ShapeTransform->Translate(position);
	graphicComp = std::make_unique<CircleGraphComp>(ShapeTransform, halfwidth, velocity, acceleration);
	physicsComp = std::make_unique<CirclePhysicsComp>(ShapeTransform,  halfwidth, velocity, acceleration);
	inUse = true;
}

Circle::~Circle()
{
}

void Circle::Update(float ElapsedDeltaTime, int width, int height)
{
	physicsComp->Update(ElapsedDeltaTime, width, height);
}


void Circle::Render(float ElapsedDeltaTime, int width, int height)
{
	graphicComp->Render(ElapsedDeltaTime,  width, height);

}
void Circle::OnCollide(int type)
{
	graphicComp->OnCollideGraphics(type); // inform comp for reaction -PC
}

bool Circle::InUse()

{

	if (!inUse)

	{

		return false;

	}

	else

	{

		return true;

	}

}
int Circle::GetType()
{
	switch (Creator)
	{
	int typenum;
	case TypeOfCreatedObject::circle:
		typenum = 0;
		return typenum;
		// gl code for color here
		break;
	case TypeOfCreatedObject::triangle:
		typenum = 1;
		return typenum;
		// gl code for color here
		break;
	case TypeOfCreatedObject::square:
		typenum = 2;
		return typenum;
		// gl code for color here
	case TypeOfCreatedObject::bound:
		typenum = 3;
		return typenum;
	}
}

void Circle::CheckBounds()
{
	if (this->GetPosition().x > 1000)
	{
		physicsComp->ReverseX();
	}
	else if (this->GetPosition().x < 0)
	{
		physicsComp->ReverseX();
	}
	if (this->GetPosition().y > 1000)
	{
		physicsComp->ReverseY();
	}
	else if (this->GetPosition().y < 0)
	{
		physicsComp->ReverseY();
	}
}

float Circle::GetHalfwidth()
{
	return halfwidth;
}

vec2 Circle::GetDirection() const
{
	return ShapeTransform->getLeftDir();
}

vec2 Circle::GetPosition() const
{
	return ShapeTransform->getPosition();
}

glm::vec2 Circle::GetDistanceMetric() const
{
	return glm::vec2(halfwidth, halfwidth); // just take x or y to be consistent - PC
}

