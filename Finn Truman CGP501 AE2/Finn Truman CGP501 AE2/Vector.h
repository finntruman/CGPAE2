#pragma once

struct Vector
{
public:
	Vector(float myX = 0, float myY = 0);
	~Vector();

	float x, y;

	bool operator== (Vector Vector2);
	Vector operator+ (Vector Vector2);
	Vector operator- (Vector Vector2);
	Vector operator* (Vector Vector2);
	Vector operator* (int num);
	Vector operator/ (Vector Vector2);
	Vector operator/ (int num);

	Vector operator+= (Vector Vector2);
	Vector operator-= (Vector Vector2);
	Vector operator*= (Vector Vector2);
	Vector operator/= (Vector Vector2);
};