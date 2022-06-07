#pragma once
#include "Obj.h"
#include "Data.h"
class Asteroide : public Obj
{
protected:

public:
	Asteroide();
	void Set_Texture(sf::Texture&);
	void Obj_Move();
	void Obj_Rotate(float);
	void Demage(int x);
	void Asteroide_Move();
};

class Big_Asteroid : public Asteroide
{
private:

public:
	Big_Asteroid();
	Big_Asteroid(sf::Texture*, int, int);
};

class Smal_Asteroid : public Asteroide
{
private:

public:
	Smal_Asteroid();
	Smal_Asteroid(sf::Texture*, sf::Vector2f&);
	Smal_Asteroid(sf::Texture*, int, int);
};

