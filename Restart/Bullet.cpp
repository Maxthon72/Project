#include "Bullet.h"

Bullet::Bullet(sf::Sprite& player)
{
	Obj_Texture.loadFromFile(Draw.string() + "\\Bullet.png");
	Obj_Sprite.setTexture(Obj_Texture);
	Obj_Sprite.setScale(2, 2);
	Obj_Sprite.setPosition(player.getPosition());
	Obj_Sprite.setRotation(player.getRotation());
	dir = player.getRotation();
	live = BULLET_LIVE;
	Obj_Move();
}

void Bullet::Obj_Move()
{
	if (((270 > deg_to_rad(dir) > 90))) {
		Move.x += BULLET_SPEED * cos(deg_to_rad(dir));
	}
	else if (((270 < deg_to_rad(dir) < 90))) {
		Move.x += BULLET_SPEED * cos(deg_to_rad(dir));
	}
	else
		Move.x += BULLET_SPEED * cos(deg_to_rad(dir));

	if (((0 > deg_to_rad(dir) > 180))) {
		Move.y += BULLET_SPEED * sin(deg_to_rad(dir));
	}
	else if (((0 < deg_to_rad(dir) < 180))) {
		Move.y += BULLET_SPEED * sin(deg_to_rad(dir));
	}
	else
		Move.y += BULLET_SPEED * sin(deg_to_rad(dir));

	for (int i = 0; i < 7; i++) {
		Bullet_Move();
		live++;
	}
	
}

void Bullet::Obj_Rotate(float)
{
}

void Bullet::Bullet_Move()
{
	Obj_Sprite.move(Move);
	live--;
}
