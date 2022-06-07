#include "Status_Window.h"

Status_Window::Status_Window()
{
	window.create(sf::VideoMode(SW_W, SW_H),SW_title, sf::Style::Resize);
	Set_Texture();
	window.setFramerateLimit(FPS);
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 0);
	Set_Texture();
}

void Status_Window::Set_Texture()
{
	W_Texture.loadFromFile(Draw.generic_string() + "\\HP.png");
	Set_Sprite();
}

void Status_Window::Set_Sprite()
{
	
}

void Status_Window::SW_Loop()
{
		//ThreadToMain.release();
		while (this->window.isOpen()){		
		MainToThread.acquire();
		//this->window.clear();
		//this->window.clear();
		this->window.clear();
		Read();
		this->window.draw(text);
		Display();
		//this->window.draw(text);
		//this->window.display();
		ThreadToMain.release();
		
	}
}

void Status_Window::Read() {

	//MainToThread.acquire();
	MyFile.open("Save.txt");
	MyFile >> live;
	MyFile >> time;
	MyFile >> score;
	MyFile.close();
	std::string textT = std::to_string(time);
	std::string textS = std::to_string(score);
	textS.resize(5);
	textT.resize(6);
	text.setString("Time: "+textT+"\n"+"Score:"+textS);
	for (int i = 0; i < live; i++) {
		sf::Sprite obj(W_Texture);
		obj.setPosition(i * 55, 130);
		this->window.draw(obj);
	}
	//ThreadToMain.release();
	
}

void Status_Window::Display()
{
	this->window.display();
}
