#include "ShapePool.h"
#include "Shape.h"
#include "Transform.h"
#include <iterator>
#include <GL/glut.h>
#include "QuadTree.h"

ShapePool::ShapePool()
{
}


ShapePool::~ShapePool() 
{
	for (int i = 0; i < POOL_SIZE; i++) 
	{
		delete(shapes[i]);
	}
}

void ShapePool::create()
{
	this->Load(); 
}

void ShapePool::Display(float ElapsedDeltaTime, int width, int height)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		shapes[i]->Render(ElapsedDeltaTime, width, height);
	}
}

void ShapePool::Update(float ElapsedDeltaTime, int width, int height)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		shapes[i]->Update(ElapsedDeltaTime, width, height);
	}
}

void ShapePool::Load() 
{
	
	for (int i = 0; i < POOL_SIZE/3; i++)
	{
		float initX = std::rand() % (40);
		float initY = std::rand() % (40);
		glm::vec2 initVel = glm::vec2(initX, initY);

		float hw = 5.0f;
		glm::vec2 vel = initVel;
		glm::vec2 acc = vec2(0.1);
		shapes[i] = new Circle(hw, vel, acc);
		

		/*float hw = 5.0f;
		glm::vec2 vel = initVel;
		glm::vec2 acc = vec2(0.1);
		shapes[i] = new Square(vel, acc, hw);*/
	}
	for (int i = POOL_SIZE / 3; i < 2*POOL_SIZE/3; i++)
	{
		float initX = std::rand() % (40);
		float initY = std::rand() % (40);
		glm::vec2 initVel = glm::vec2(initX, initY);

		float hw = 5.0f;
		glm::vec2 vel = initVel;
		glm::vec2 acc = vec2(0.1);
		shapes[i] = new Triangle(hw, vel, acc);
		
	}
	for (int i = 2 * POOL_SIZE / 3; i < POOL_SIZE; i++)
	{
		float initX = std::rand() % (40);
		float initY = std::rand() % (40);
		glm::vec2 initVel = glm::vec2(initX, initY);

		float hw = 5.0f;
		glm::vec2 vel = initVel;
		glm::vec2 acc = vec2(0.1);
		shapes[i] = new Square(vel, acc, hw);
	}
}

int ShapePool::GetSize() const
{
	return POOL_SIZE;
}

void ShapePool::Clean()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		shapes[i]->pNextObject = nullptr;
	}
}
