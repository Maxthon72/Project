#include "Asteroide.h"

Asteroide::Asteroide()
{
}

void Asteroide::Set_Texture(sf::Texture& texture)
{
	Obj_Texture = texture;
}


void Asteroide::Obj_Move()
{
	if (((270 > deg_to_rad(dir) > 90))) {
		Move.x = ASTEROIDE_SPEED * cos(deg_to_rad(this->dir));
	}
	else if (((270 < deg_to_rad(dir) < 90))) {
		Move.x = ASTEROIDE_SPEED * cos(deg_to_rad(this->dir));
	}
	else
		Move.x = ASTEROIDE_SPEED * cos(deg_to_rad(this->dir));

	if (((0 > deg_to_rad(dir) > 180))) {
		Move.y = ASTEROIDE_SPEED * sin(deg_to_rad(this->dir));
	}
	else if (((0 < deg_to_rad(dir) < 180))) {
		Move.y = ASTEROIDE_SPEED * sin(deg_to_rad(this->dir));
	}
	else
		Move.y = ASTEROIDE_SPEED * sin(deg_to_rad(this->dir));
}

void Asteroide::Obj_Rotate(float x)
{
	this->dir = x;
	Obj_Move();
}

void Asteroide::Demage(int x)
{
}

void Asteroide::Asteroide_Move()
{
	Obj_Sprite.move(Move);
}

Big_Asteroid::Big_Asteroid()
{
	Obj_Sprite.setScale(BIG_ASTEROIDE_SCALE, BIG_ASTEROIDE_SCALE);
	
}

Big_Asteroid::Big_Asteroid(sf::Texture* texture, int x, int y)
{
	Obj_Texture = *texture;
	Set_Texture(Obj_Texture);
	Set_Sprite();
	Set_Live(BIG_ASTEROIDE_LIVE);
	Obj_Sprite.setScale(BIG_ASTEROIDE_SCALE, BIG_ASTEROIDE_SCALE);
	int As_W = Obj_Sprite.getGlobalBounds().width;
	int As_H = Obj_Sprite.getGlobalBounds().height;
	Obj_Sprite.setOrigin(As_W / 2, As_H / 2);
	Obj_Sprite.setPosition(x, y);
	
}


Smal_Asteroid::Smal_Asteroid()
{
	
}

Smal_Asteroid::Smal_Asteroid(sf::Texture* texture, sf::Vector2f& pos)
{
	Obj_Texture = *texture;
	Set_Texture(Obj_Texture);
	Set_Sprite();
	Set_Live(SMALL_ASTEROIDE_LIVE);
	Obj_Sprite.setScale(SMALL_ASTEROIDE_SCALE, SMALL_ASTEROIDE_SCALE);
	int As_W = Obj_Sprite.getGlobalBounds().width;
	int As_H = Obj_Sprite.getGlobalBounds().height;
	Obj_Sprite.setOrigin(As_W / 2, As_H / 2);
	Obj_Sprite.setPosition(pos);
	Obj_Move();
}

Smal_Asteroid::Smal_Asteroid(sf::Texture* texture, int x, int y)
{
	Obj_Texture = *texture;
	Set_Texture(Obj_Texture);
	Set_Sprite();	
	Set_Live(SMALL_ASTEROIDE_LIVE);
	Obj_Sprite.setScale(SMALL_ASTEROIDE_SCALE, SMALL_ASTEROIDE_SCALE);
	int As_W = Obj_Sprite.getGlobalBounds().width;
	int As_H = Obj_Sprite.getGlobalBounds().height;
	Obj_Sprite.setOrigin(As_W / 2, As_H / 2);
	Obj_Sprite.setPosition(x, y);
	Obj_Move();

}