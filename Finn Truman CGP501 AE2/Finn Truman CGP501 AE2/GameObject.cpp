#include "GameObject.h"
#include "GameManager.h"
#include "Actor.h"
#include "Level.h"
//#include "Sprite.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{

}

int GameObject::Clamp(int toClamp, int min, int max)
{
	if (toClamp < min) return min;
	else if (toClamp > max) return max;
}

float GameObject::DistanceTo(Vector point1, Vector point2)
{
	Vector pointB(point1.x, point2.y);

	float AtoB = pointB.x - point1.x;
	float BtoC = point2.y - pointB.y;

	//sqrt(A*A + B*B)
	return std::sqrt(AtoB*AtoB + BtoC*BtoC);
}

int GameObject::Sign(float num)
{
	return num / abs(num); //Sign returns either 1, 0 or -1, depending if the parameter is positive, 0, or negative respectively
}

//COLLISION METHODS
bool GameObject::CollisionPoint_Map(float x, float y)
{
	Vector mapVector = p_level->WorldSpaceToLevelSpace(x, y);
	if (p_level->GetLevelCoord(mapVector) == '.')
	{
		return false; //it was a dot, no collision, return false
	}
	else return true; //it was something other than a dot, collision, return true
}

bool GameObject::CollisionPoint_Map(Vector point)
{
	return CollisionPoint_Map(point.x, point.y);
}

bool GameObject::CollisionSprite_Map(float x, float y)
{
	return CollisionSprite_Map(this, { x, y });
}

bool GameObject::CollisionSprite_Map(Vector position)
{
	return CollisionSprite_Map(this, position);
}

bool GameObject::CollisionSprite_Map(GameObject* collision, float x, float y)
{
	CollisionSprite_Map(collision, { x, y });
}

bool GameObject::CollisionSprite_Map(GameObject* collision, Vector position)
{
	Sprite spr = collision->m_sprite;
	Vector sprTL(position); //these four vectors create the phantom sprite, which is equal to the collision box of the Character that called this function
	Vector sprTR(position + Vector(spr.GetCollisionWidth() - 1, 0)); //they stand for TopLeft, TopRight, BottomLeft and BottomRight
	Vector sprBL(position + Vector(0, spr.GetCollisionHeight() - 1));
	Vector sprBR(position + Vector(spr.GetCollisionWidth() - 1, spr.GetCollisionHeight() - 1));

	return (p_manager->CollisionPoint_Map(sprTL) || p_manager->CollisionPoint_Map(sprTR) || p_manager->CollisionPoint_Map(sprBL) || p_manager->CollisionPoint_Map(sprBR)); //so if any of these points are colliding, the sprite as a whole is colliding, and returns true
}

bool GameObject::CollisionSprite_Object(Actor* collision1, Actor* collision2)
{
	float spr1_L, spr1_T, spr1_R, spr1_B, spr2_L, spr2_T, spr2_R, spr2_B;

	spr1_L = collision1->GetPosition().x;
	spr1_R = spr1_L + collision1->GetSprite()->GetCollisionWidth() - 1;
	spr1_T = collision1->GetPosition().y;
	spr1_B = spr1_T + collision1->GetSprite()->GetCollisionHeight() - 1;

	spr2_L = collision2->GetPosition().x;
	spr2_R = spr2_L + collision2->GetSprite()->GetCollisionWidth() - 1;
	spr2_T = collision2->GetPosition().y;
	spr2_B = spr2_T + collision2->GetSprite()->GetCollisionHeight() - 1;

	if (spr1_L < spr2_R &&
		spr1_R > spr2_L &&
		spr1_T < spr2_B &&
		spr1_B > spr2_T)
	{
		return true;
	}
	else return false;
}