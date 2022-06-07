#pragma once
#include "Obj.h"
#include "Data.h"
class Bullet : public Obj
{
private:
public:
	Bullet(sf::Sprite&);
	void Obj_Move();
	void Obj_Rotate(float);
	void Bullet_Move();
};

