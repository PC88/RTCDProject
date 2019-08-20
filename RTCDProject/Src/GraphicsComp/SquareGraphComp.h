#pragma once
#include "GraphicsComp.h"
#include <memory>
#include <glm/glm.hpp>

class SquareGraphComp :
	public GraphicsComp
{
public:
	SquareGraphComp(std::shared_ptr<Transform> ShapeTransform, glm::vec2& vel, glm::vec2& acc, float& hw);
	virtual ~SquareGraphComp();

	 void Render(float ElapsedDeltaTime, int width, int height) ;

	 void OnCollideGraphics(int type);

private:

	std::shared_ptr<Transform> ShapeTransform;
	float halfwidth;
	glm::vec2 position;

	glm::vec2 topLeft;
	glm::vec2 topRight;
	glm::vec2 bottomLeft;
	glm::vec2 bottomRight;

	glm::vec2 ToGlutRefSystem(glm::vec2 p, int width, int height);
};

