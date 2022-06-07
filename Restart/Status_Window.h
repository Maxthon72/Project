#pragma once
#include "Window.h"
#include "Data.h"
#include <iostream>
#include <string>
class Status_Window : public Window
{
private:
	sf::Vector2f position;
	int live;
	int score;
	float time;
	sf::Font font;
	sf::Text text;
	std::ifstream MyFile;
public:
	Status_Window();
	void Set_Texture();
	void Set_Sprite();
	void SW_Loop();
	void Display();
	
	void Read();
};

