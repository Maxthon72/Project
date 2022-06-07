#include "Main_Window.h"

Main_Window::Main_Window()
{
	window.create(sf::VideoMode(W, H), title, sf::Style::Close);
	Set_Texture();
	window.setFramerateLimit(30);
}

void Main_Window::Set_Texture()
{
	W_Texture.loadFromFile(Draw.generic_string() + "\\Cosmos.png");
	SG_Texture.loadFromFile(Draw.generic_string() + "\\Start.png");
	GG_Texture.loadFromFile(Draw.generic_string() + "\\GameOver.png");
	Set_Sprite();
}

void Main_Window::Set_Sprite()
{
	W_Sprite.setTexture(SG_Texture);
}

void Main_Window::Set_Sprite(int& state)
{
	if (state == 0)
		W_Sprite.setTexture(SG_Texture);
	else if (state == 1)
		W_Sprite.setTexture(W_Texture);
	else
		W_Sprite.setTexture(GG_Texture);
}

void Main_Window::Wrap(sf::Sprite& obj)
{
	float x = obj.getPosition().x;
	float y = obj.getPosition().y;
	if (x > W || x < 0)
		obj.setPosition(abs(x-W), y);
	if(y>H||y<0)
		obj.setPosition(x, abs(y-H));
}
