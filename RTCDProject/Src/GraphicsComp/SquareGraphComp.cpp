#include "SquareGraphComp.h"
#include "Transform.h"
#include "SingletonGraphStates.h"
#include <iostream>


SquareGraphComp::SquareGraphComp(std::shared_ptr<Transform> ShapeTransform, glm::vec2& vel, glm::vec2& acc, float& hw)
	: ShapeTransform(ShapeTransform), halfwidth(hw),
	topLeft(ShapeTransform->getPosition().x -hw,ShapeTransform->getPosition().y -hw),
	topRight(ShapeTransform->getPosition().x + hw, ShapeTransform->getPosition().y - hw),
	bottomLeft(ShapeTransform->getPosition().x - hw, ShapeTransform->getPosition().y + hw),
	bottomRight(ShapeTransform->getPosition().x + hw, ShapeTransform->getPosition().y + hw)
{
	LastHtObject = GraphicsComp::Nothing;
}

SquareGraphComp::~SquareGraphComp()
{
}

void SquareGraphComp::Render(float ElapsedDeltaTime, int width, int height)
{
	topLeft = vec2(ShapeTransform->getPosition().x - halfwidth, ShapeTransform->getPosition().y - halfwidth);
	topRight = vec2(ShapeTransform->getPosition().x + halfwidth, ShapeTransform->getPosition().y - halfwidth);
	bottomLeft = vec2(ShapeTransform->getPosition().x - halfwidth, ShapeTransform->getPosition().y + halfwidth);
	bottomRight = vec2(ShapeTransform->getPosition().x + halfwidth, ShapeTransform->getPosition().y + halfwidth);
	
	//std::cout<< "POINT SQUARE " << topLeft.x << std::endl;

	position = ShapeTransform->getPosition();
	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);

   
	glBegin(GL_QUADS);
	
	//NOTE: glColor3f(color.r, color.g, color.b) // this is basically whats being done here to avoid copying, and to use the flyweight pattern -PC
	// it may be seen as somewhat "unimpactfull" in this project as its a ref to 9 simple color outcomes as opposed to actual large objects
	// however this is there so show the utilization of what an engine COULD do... if this was not GLUT, and I had more time/experience for example I would have a renderer which had information obound to
	// uniforms like modern OpenGL does, or even further a Material like a REAL game engine, but the principles used here are the same that they use on a smaller scale, but none the less
	// show the usage to be proper and I hope show understanding to a degree. -PC
	switch (LastHtObject)
	{
	case GraphicsComp::Nothing:
		// gl code for color here
		glColor3f(SingletonGraphStates::instance().getSquareDefault().r,
			SingletonGraphStates::instance().getSquareDefault().g,
			SingletonGraphStates::instance().getSquareDefault().b);
		break;
	case GraphicsComp::Triangle:
		// gl code for triangle here
		glColor3f(SingletonGraphStates::instance().getSquareTriangle().r,
			SingletonGraphStates::instance().getSquareTriangle().g,
			SingletonGraphStates::instance().getSquareTriangle().b);
		break;
	case GraphicsComp::Circle:
		// gl code for circle 
		glColor3f(SingletonGraphStates::instance().getSquareCircle().r,
			SingletonGraphStates::instance().getSquareCircle().g,
			SingletonGraphStates::instance().getSquareCircle().b);
		break;
	case GraphicsComp::Square:
		// gl code for circle
		glColor3f(SingletonGraphStates::instance().getSquareSquare().r,
			SingletonGraphStates::instance().getSquareSquare().g,
			SingletonGraphStates::instance().getSquareSquare().b);
		break;
	}

	glm::vec2 v(ToGlutRefSystem(topLeft, width, height));
	glVertex2d(v.x, v.y);

	glm::vec2 v1(ToGlutRefSystem(topRight, width, height));
	glVertex2d(v1.x, v1.y);

	glm::vec2 v2(ToGlutRefSystem(bottomRight, width, height));
	glVertex2d(v2.x, v2.y);

	glm::vec2 v3(ToGlutRefSystem(bottomLeft, width, height));
	glVertex2d(v3.x, v3.y);

	glEnd();
	glFlush();
}


void SquareGraphComp::OnCollideGraphics(int type)
{
	if (type == 0)
	{
		LastHtObject = GraphicsComp::Circle;
	}
	if (type == 1)
	{
		LastHtObject = GraphicsComp::Triangle;
	}
	if (type == 2)
	{
		LastHtObject = GraphicsComp::Square;
	}
}

glm::vec2 SquareGraphComp::ToGlutRefSystem(glm::vec2 p, int width, int height)
{
	glm::vec2 v((p.x / (width*0.5)) - 1, (p.y / (height*0.5)) - 1);
	return v;
}
