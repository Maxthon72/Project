#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#define M_PI 3.14159265358979323846
class Obj
{
protected:
	sf::Texture Obj_Texture;
	sf::Sprite Obj_Sprite;
	sf::Vector2f Move;
	int live;
	float dir;
public:
	void Set_Sprite(){ Obj_Sprite.setTexture(Obj_Texture); }
	virtual void Obj_Move() = 0;
	virtual void Obj_Rotate(float) = 0;
	float Pitagoras(float x, float y);
	float deg_to_rad(float deg);
	float Get_Dir() { return dir; }
	int Get_Live() { return live; }
	sf::Sprite& Get_Sprite() { return Obj_Sprite; }
	void Set_Live(int x) { live = x; }
	void Minus_Live() { live--; }
	bool Chcek_lives();
	void Kill() { live = 0; }
};

