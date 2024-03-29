#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include <chrono>

class Transform;
enum TypeOfCreatedObject { circle, triangle, square, bound}; // this is reflection meta data which will tell the event manager what type the lower object is -PC
class Shape
{
public:
	Shape();
	virtual ~Shape();


	Shape* pNextObject; // Pointer to next object in linked list // C.Erickson RTCD has to be public for QT -PC


	virtual void Update(float ElapsedDeltaTime, int width, int height) = 0;

	virtual bool InUse() = 0;

	virtual void Render(float ElapsedDeltaTime, int width, int height) = 0;

	virtual glm::vec2 GetDirection() const = 0;

	virtual glm::vec2 GetDistanceMetric() const = 0;

	virtual void OnCollide(int type) = 0;

	virtual void CheckBounds() = 0;

	virtual float GetHalfwidth() = 0;

	virtual glm::vec2 GetPosition() const = 0; // returns position, but this will also be the centre by definition - see constructor -PC

	virtual int GetType() = 0; // this will be reflect the value of the Enum thus giving us the type without casting. -PC
private:

protected:


	glm::vec2 direction;

	glm::vec2 position;

	std::shared_ptr<Transform> ShapeTransform; 
		
	TypeOfCreatedObject Creator;

};