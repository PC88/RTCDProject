#include "TriangleGraphComp.h"
#include "SingletonGraphStates.h"
#include "Transform.h"
#include <iostream>

TriangleGraphComp::TriangleGraphComp(std::shared_ptr<Transform> ShapeTransform, float& halfwidth, glm::vec2& vel, glm::vec2& acc)
	:ShapeTransform(ShapeTransform), halfwidth(halfwidth),
	topPoint(ShapeTransform->getPosition().x,ShapeTransform->getPosition().y - halfwidth),
	leftPoint(ShapeTransform->getPosition().x - halfwidth, ShapeTransform->getPosition().y + halfwidth), 
	rightPoint(ShapeTransform->getPosition().x + halfwidth, ShapeTransform->getPosition().y + halfwidth)
{
	LastHtObject = GraphicsComp::Nothing; // init to default color -PC
}

TriangleGraphComp::~TriangleGraphComp()
{
}

void TriangleGraphComp::Render(float ElapsedDeltaTime, int width, int height) // COPY PASTE OF SQUARE GRAPHCOMP
{
	topPoint = vec2(ShapeTransform->getPosition().x, ShapeTransform->getPosition().y - halfwidth);
	leftPoint = vec2(ShapeTransform->getPosition().x - halfwidth, ShapeTransform->getPosition().y + halfwidth);
	rightPoint = vec2(ShapeTransform->getPosition().x + halfwidth, ShapeTransform->getPosition().y + halfwidth);

	//std::cout << "POINT TRI " << topPoint.x << std::endl;

	position = ShapeTransform->getPosition();
	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);

	glm::vec2 p((position.x / (width*0.5)) - 1, (position.y / (height*0.5)) - 1);
	

	glBegin(GL_POLYGON);
	
	//NOTE: glColor3f(color.r, color.g, color.b) // this is basically whats being done here to avoid copying, and to use the flyweight pattern -PC
	// it may be seen as somewhat "unimpactfull" in this project as its a ref to 9 simple color outcomes as opposed to actual large objects
	// however this is there so show the utilization of what an engine COULD do... if this was not GLUT, and I had more time/experience for example I would have a renderer which had information obound to
	// uniforms like modern OpenGL does, or even further a Material like a REAL game engine, but the principles used here are the same that they use on a smaller scale, but none the less
	// show the usage to be proper and I hope show understanding to a degree. -PC
	switch (LastHtObject)
	{
	case GraphicsComp::Nothing:
		 //gl code for color here
		glColor3f(SingletonGraphStates::instance().getTriangleDefault().r,
			SingletonGraphStates::instance().getTriangleDefault().g,
			SingletonGraphStates::instance().getTriangleDefault().b);
		break;
	case GraphicsComp::Triangle:
		 //gl code for triangle here
		glColor3f(SingletonGraphStates::instance().getTriangleTriangle().r,
			SingletonGraphStates::instance().getTriangleTriangle().g,
			SingletonGraphStates::instance().getTriangleTriangle().b);
		break;
	case GraphicsComp::Circle:
		 //gl code for circle 
		glColor3f(SingletonGraphStates::instance().getTriangleCircle().r,
			SingletonGraphStates::instance().getTriangleCircle().g,
			SingletonGraphStates::instance().getTriangleCircle().b);
		break;
	case GraphicsComp::Square:
		 //gl code for circle
		glColor3f(SingletonGraphStates::instance().getTriangleSquare().r,
			SingletonGraphStates::instance().getTriangleSquare().g,
			SingletonGraphStates::instance().getTriangleSquare().b);
		break;
	}

	glm::vec2 v(ToGlutRefSystem(topPoint, width, height));
	glVertex2d(v.x, v.y);
	
	//std::cout << v.x << " " << v.y << std::endl;

	glm::vec2 v1(ToGlutRefSystem(leftPoint, width, height));
	glVertex2d(v1.x,v1.y);

	//std::cout << v1.x << " " << v1.y << std::endl;
	
	glm::vec2 v2(ToGlutRefSystem(rightPoint, width, height));
	glVertex2d(v2.x, v2.y);
	
	
	glEnd();
	glFlush();
}

glm::vec2 TriangleGraphComp::ToGlutRefSystem(glm::vec2 p, int width, int height)
{	
	glm::vec2 v((p.x / (width*0.5)) - 1, (p.y / (height*0.5)) - 1);
	return v;
}

void TriangleGraphComp::OnCollideGraphics(int type)
{
	if (type == 0)
	{
		LastHtObject = GraphicsComp::Circle;
	}
	if(type == 1)
	{
		LastHtObject = GraphicsComp::Triangle;
	}
	if (type == 2)
	{
		LastHtObject = GraphicsComp::Square;
	}
}
