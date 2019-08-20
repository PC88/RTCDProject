#pragma once
#include "GraphicsComp.h"

class CircleGraphComp :
	public GraphicsComp
{
public:
	CircleGraphComp(std::shared_ptr<Transform> ShapeTransform, float& r, glm::vec2& vel, glm::vec2& acc);
	virtual ~CircleGraphComp();

	void Render(float ElapsedDeltaTime, int width, int height);

	void OnCollideGraphics(int type);

private:

	glm::vec2 ToGlutRefSystem(glm::vec2 p, int width, int height);

	float radius;

	glm::vec2 position;
	std::shared_ptr<Transform> ShapeTransform;
};

