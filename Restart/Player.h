#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Data.h"
#include <iostream>

class Player : public Obj
{
private:
	sf::Vector2f Buff;
	bool colision;
public:
	Player();
	void Set_Texture();
	void Obj_Controlle();
	void Obj_Move();
	void Obj_Rotate(float);
	bool MAX_Speed();
	void Set_Speed();
	void Reset();
	void Colided() { colision = true; }
	bool Colided_Q() { return colision; }
	Bullet* Shoot();
};

