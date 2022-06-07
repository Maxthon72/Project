#pragma once
#include "Window.h"
#include "Data.h"
class Main_Window : public Window
{
private:
	sf::Texture SG_Texture;
	sf::Texture GG_Texture;
public:
	Main_Window();
	void Set_Texture();
	void Set_Sprite();
	void Set_Sprite(int&);
	void Wrap(sf::Sprite&);
};

