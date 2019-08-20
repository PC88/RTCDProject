#pragma once
#include "GraphicsComp.h"
#include <memory>

class Transform;

class TriangleGraphComp :
	public GraphicsComp
{
public:
	TriangleGraphComp(std::shared_ptr<Transform> ShapeTransform, float& hw, glm::vec2& vel, glm::vec2& acc);
	virtual ~TriangleGraphComp();

	void Render(float ElapsedDeltaTime, int width, int height) ;

	virtual void OnCollideGraphics(int type);

private:
	float halfwidth;
	
	glm::vec2 topPoint;
	glm::vec2 leftPoint;
	glm::vec2 rightPoint;

	glm::vec2 position;

	std::shared_ptr<Transform> ShapeTransform;

	glm::vec2 ToGlutRefSystem(glm::vec2 p, int width, int height);
};

