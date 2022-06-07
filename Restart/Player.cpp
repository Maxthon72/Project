#include "Player.h"

Player::Player()
{
	Set_Texture();
	Set_Sprite();
	Obj_Sprite.setOrigin(PLAYER_X / 2, PLAYER_Y / 2);
	Obj_Sprite.setPosition(W / 2, H / 2);
	Obj_Sprite.setRotation(0);
	Move.x = 0;
	Move.y = 0;
	Set_Live(3);
	dir = 0;
}

void Player::Set_Texture()
{
	Obj_Texture.loadFromFile(Draw.generic_string() + "\\Player.png");
}


void Player::Obj_Controlle()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		dir += PLAYER_ROT_L;
		Obj_Rotate(PLAYER_ROT_L);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		dir += PLAYER_ROT_R;
		Obj_Rotate(PLAYER_ROT_R);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Buff = Move;
		if (((270 > deg_to_rad(dir) > 90))) {
			Move.x += PLAYER_SPEED * cos(deg_to_rad(dir));
		}
		else if (((270 < deg_to_rad(dir) < 90))) {
			Move.x += PLAYER_SPEED * cos(deg_to_rad(dir));
		}
		else
			Move.x += PLAYER_SPEED * cos(deg_to_rad(dir));

		if (((0 > deg_to_rad(dir) > 180))) {
			Move.y += PLAYER_SPEED * sin(deg_to_rad(dir));
		}
		else if (((0 < deg_to_rad(dir) < 180))) {
			Move.y += PLAYER_SPEED * sin(deg_to_rad(dir));
		}
		else
			Move.y += PLAYER_SPEED * sin(deg_to_rad(dir));
	}
}

void Player::Obj_Move()
{
	if (MAX_Speed())
		Set_Speed();
	Obj_Sprite.move(Move.x, Move.y);
	//std::cout << "X : " << Move.x << " Y : " << Move.y << std::endl;
}

void Player::Obj_Rotate(float alfa)
{
	dir = fmod(360 + fmod(dir, 360), 360);
	Obj_Sprite.rotate(alfa);
}

bool Player::MAX_Speed()
{
	float c = sqrt(pow(Move.x, 2) + pow(Move.y, 2));
	if (c >= PLAYER_MAX_SPEED)
		return true;
	return false;
}

void Player::Set_Speed()
{
	if (abs(Buff.x) < abs(Move.x))
		Move.x = Buff.x;
	if (abs(Buff.y) < abs(Move.y))
		Move.y = Buff.y;
}

void Player::Reset()
{
	Obj_Sprite.setPosition(W / 2, H / 2);
	Obj_Sprite.setRotation(0);
	Move.x = 0;
	Move.y = 0;
	Buff.x = 0;
	Buff.y = 0;
	dir = 0;
	colision = false;
}

Bullet* Player::Shoot()
{
	Bullet* bu = new Bullet(Obj_Sprite);
	return bu;
}
