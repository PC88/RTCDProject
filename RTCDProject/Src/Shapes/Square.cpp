#include "Square.h"
#include "Transform.h"
#include <ctime>


Square::Square(vec2& vel, vec2& acc, float& hw)
	: acceleration(acc), velocity(vel), halfwidth(hw) // delete graph and physic comps and change transform VIA TRANSLATE IN MOVE FROM LABS
{
	float initX = std::rand() % (1000 -  1); // make initial position between screen limits does hard code at the moment -PC
	float initY = std::rand() % (1000 -  1);

	Creator = TypeOfCreatedObject::square; // define meta data -PC

	ShapeTransform = std::make_shared<Transform>();
	position = vec2(initX, initY); // init to random -PC // this actually has to be set in the transform -PC
	ShapeTransform->Translate(position);// set Shape transform to position initially -PC - TODO copy this to the other shape classes -PC
	graphicComp = std::make_unique<SquareGraphComp>(ShapeTransform, velocity, acceleration, halfwidth); // set up graphics and physics comps -PC
	physicsComp = std::make_unique<SquarePhysicsComp>(ShapeTransform, velocity, acceleration, halfwidth);
	inUse = true;
}


Square::~Square()
{
}

void Square::Update(float ElapsedDeltaTime, int width, int height)
{
	physicsComp->Update(ElapsedDeltaTime, width, height);
}

void Square::Render(float ElapsedDeltaTime, int width, int height)
{
	graphicComp->Render(ElapsedDeltaTime, width, height);
}

void Square::OnCollide(int type)
{
	graphicComp->OnCollideGraphics(type); // inform comp for reaction -PC
}

void Square::CheckBounds()
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

bool Square::InUse()
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


int Square::GetType()
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
	    break; 
	}
}

glm::vec2 Square::GetDistanceMetric() const
{
	return glm::vec2(halfwidth, halfwidth);
}

float Square::GetHalfwidth()
{
	return halfwidth;
}

glm::vec2 Square::GetDirection() const
{
	return ShapeTransform->getLeftDir();// not correct I believe - PC
}

glm::vec2 Square::GetPosition() const
{
	return ShapeTransform->getPosition();
}
