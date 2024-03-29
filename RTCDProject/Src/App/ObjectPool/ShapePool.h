#pragma once
#include <memory>
#include <vector>
#include <chrono>

class Shape;
class Transform;

#include "Square.h"
#include "Circle.h"
#include "Triangle.h"

class ShapePool
{
public:
	ShapePool();
	virtual ~ShapePool();

	static const int POOL_SIZE = 120;

	void create();

	void Display(float ElapsedDeltaTime, int width, int height);

	void Update(float ElapsedDeltaTime, int width, int height);

	void Load();

	int GetSize() const;

	void Clean();

	Shape* shapes[POOL_SIZE];
private:


};

