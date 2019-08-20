#include "CircleGraphComp.h"
#include "Transform.h"
#include "SingletonGraphStates.h"
#include <iostream>

#include <glm/gtc/constants.hpp> 
#include <GL/glut.h>

CircleGraphComp::CircleGraphComp(std::shared_ptr<Transform> ShapeTransform, float& r, glm::vec2& vel, glm::vec2& acc)
	: ShapeTransform(ShapeTransform), radius(r)
{
	LastHtObject = LastcollidedWith::Nothing;
}

CircleGraphComp::~CircleGraphComp()
{
}

void CircleGraphComp::Render(float ElapsedDeltaTime, int width, int height)
{
	position = ShapeTransform->getPosition();
	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);

   // Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);

	//NOTE: glColor3f(color.r, color.g, color.b) // this is basically whats being done here to avoid copying, and to use the flyweight pattern -PC
	// it may be seen as somewhat "unimpactfull" in this project as its a ref to 9 simple color outcomes as opposed to actual large objects
	// however this is there so show the utilization of what an engine COULD do... if this was not GLUT, and I had more time/experience for example I would have a renderer which had information obound to
	// uniforms like modern OpenGL does, or even further a Material like a REAL game engine, but the principles used here are the same that they use on a smaller scale, but none the less
	// show the usage to be proper and I hope show understanding to a degree. -PC
	switch (LastHtObject) 
	{
	case GraphicsComp::Nothing:
		// gl code for color here
		glColor3f(SingletonGraphStates::instance().getCircleDefault().r, 
			SingletonGraphStates::instance().getCircleDefault().g, 
			SingletonGraphStates::instance().getCircleDefault().b);
		break;
	case GraphicsComp::Triangle: 
		// gl code for triangle here
		glColor3f(SingletonGraphStates::instance().getCircleTriangle().r,
			SingletonGraphStates::instance().getCircleTriangle().g, 
			SingletonGraphStates::instance().getCircleTriangle().b);
		break;
	case GraphicsComp::Circle:
		// gl code for circle 
		glColor3f(SingletonGraphStates::instance().getCircleCircle().r,
			SingletonGraphStates::instance().getCircleCircle().g,
			SingletonGraphStates::instance().getCircleCircle().b);
		break;
	case GraphicsComp::Square:
		// gl code for circle
		glColor3f(SingletonGraphStates::instance().getCircleSquare().r,
			SingletonGraphStates::instance().getCircleSquare().g,
			SingletonGraphStates::instance().getCircleSquare().b);
		break;
	default: GraphicsComp::Nothing;
		glColor3f(SingletonGraphStates::instance().getCircleDefault().r,
			SingletonGraphStates::instance().getCircleDefault().g,
			SingletonGraphStates::instance().getCircleDefault().b);
		break;
	}


	glm::vec2 centre(ToGlutRefSystem(position, width, height));
	glVertex2f((float)centre.x, (float)centre.y);	// Center of circle

	int numSegments = 10;
	float angle;
	for (int i = 0; i <= numSegments; i++)
	{					// Last vertex same as first vertex
		angle = i * 2.0f * pi<float>()/ numSegments;	

		glm::vec2 circPoints(centre.x + (cos(angle) * (2.0f * radius / width)* aspectRatio),
			centre.y + (sin(angle) * (2.0f * radius / height)));
		ToGlutRefSystem(circPoints,width,height);
		glVertex2f(circPoints.x, circPoints.y);
	}

	glEnd();
	glFlush();
}

void CircleGraphComp::OnCollideGraphics(int type)
{
	if (type == 0) //r
	{
		LastHtObject = GraphicsComp::Circle;
	}
	if (type == 1) //g
	{
		LastHtObject = GraphicsComp::Triangle;
	}
	if (type == 2) //b
	{
		LastHtObject = GraphicsComp::Square;
	}
}

glm::vec2 CircleGraphComp::ToGlutRefSystem(glm::vec2 p, int width, int height)
{
	glm::vec2 v((p.x / (width*0.5)) - 1, (p.y / (height*0.5)) - 1);
	return v;
}

