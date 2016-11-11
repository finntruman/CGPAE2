#include "Vector.h"

Vector::Vector(float myX, float myY)
	: x(myX), y(myY)
{}

Vector::~Vector()
{}

bool Vector::operator==(Vector Vector2)
{
	Vector Vector1 = *this;
	return (Vector1.x == Vector2.x && Vector1.y == Vector2.y);
}

Vector Vector::operator+(Vector Vector2)
{
	Vector Vector1 = *this;
	return Vector(Vector1.x + Vector2.x, Vector1.y + Vector2.y);
}

Vector Vector::operator-(Vector Vector2)
{
	Vector Vector1 = *this;
	return Vector(Vector1.x - Vector2.x, Vector1.y - Vector2.y);
}

Vector Vector::operator*(Vector Vector2)
{
	Vector Vector1 = *this;
	return Vector(Vector1.x * Vector2.x, Vector1.y * Vector2.y);
}

Vector Vector::operator*(int num)
{
	Vector Vector1 = *this;
	return Vector(Vector1.x * num, Vector1.y * num);
}

Vector Vector::operator/(Vector Vector2)
{
	Vector Vector1 = *this;
	return Vector(Vector1.x / Vector2.x, Vector1.y / Vector2.y);
}

Vector Vector::operator/(int num)
{
	Vector Vector1 = *this;
	return Vector(Vector1.x / num, Vector1.y / num);
}

Vector Vector::operator+=(Vector Vector2)
{
	Vector Vector1 = *this;
	Vector1.x += Vector2.x;
	Vector1.y += Vector2.y;
	return Vector1;
}

Vector Vector::operator-=(Vector Vector2)
{
	Vector Vector1 = *this;
	Vector1.x -= Vector2.x;
	Vector1.y -= Vector2.y;
	return Vector1;
}

Vector Vector::operator*=(Vector Vector2)
{
	Vector Vector1 = *this;
	Vector1.x *= Vector2.x;
	Vector1.y *= Vector2.y;
	return Vector1;
}

Vector Vector::operator/=(Vector Vector2)
{
	Vector Vector1 = *this;
	Vector1.x /= Vector2.x;
	Vector1.y /= Vector2.y;
	return Vector1;
}
