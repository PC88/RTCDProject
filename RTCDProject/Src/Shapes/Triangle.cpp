#include "Triangle.h"
#include "TriangleGraphComp.h"
#include "TrianglePhysicsComp.h"
#include "Transform.h"
#include <memory>


Triangle::Triangle(float& hw, glm::vec2& vel, glm::vec2& acc)
	: halfwidth(hw), velocity(vel), acceleration(acc)
{

	float initX = std::rand() % (1000 - 1);
	float initY = std::rand() % (1000 - 1);

	Creator = TypeOfCreatedObject::triangle; // define meta data -PC


	ShapeTransform = std::make_shared<Transform>();
	position = vec2(initX, initY); // init to random -PC // this actually has to be set in the transform -PC
	ShapeTransform->Translate(position);
	graphicComp = std::make_unique<TriangleGraphComp>(ShapeTransform, halfwidth, velocity, acceleration);
	physicsComp = std::make_unique<TrianglePhysicsComp>(ShapeTransform, halfwidth, velocity, acceleration);
	inUse = true;

	topPoint = glm::vec2(ShapeTransform->getPosition().x, ShapeTransform->getPosition().y - halfwidth);
	leftPoint = glm::vec2(ShapeTransform->getPosition().x - halfwidth, ShapeTransform->getPosition().y + halfwidth); // this is defined because of philosophy of the project, it does quite literally do nothing -PC
	rightPoint = glm::vec2(ShapeTransform->getPosition().x + halfwidth, ShapeTransform->getPosition().y + halfwidth);
}

Triangle::~Triangle()
{
}

void Triangle::Update(float ElapsedDeltaTime, int width, int height)
{
	physicsComp->Update(ElapsedDeltaTime, width, height);
}

void Triangle::OnCollide(int type)
{
	graphicComp->OnCollideGraphics(type); 
}

void Triangle::CheckBounds()
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


void Triangle::Render(float ElapsedDeltaTime, int width, int height)
{
	graphicComp->Render(ElapsedDeltaTime, width, height);
}

vec2 Triangle::GetDirection() const
{
	return ShapeTransform->getUpDir();
}

vec2 Triangle::GetPosition() const
{
	return ShapeTransform->getPosition();
}

glm::vec2 Triangle::GetDistanceMetric() const
{
	return glm::vec2(halfwidth, halfwidth);
}


int Triangle::GetType()
{
	switch (Creator) // why is this undefined -PC
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
	case TypeOfCreatedObject::bound:
		typenum = 3;
		return typenum;
		// gl code for color here
		break;
	}
}


bool Triangle::InUse()
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

float Triangle::GetHalfwidth()
{
	return halfwidth;
}

glm::vec2 Triangle::GetTopPoint()
{
	return topPoint;
}

glm::vec2 Triangle::GetLeftPoint()
{
	return leftPoint;
}

glm::vec2 Triangle::GetRightPoint()
{
	return rightPoint;
}
