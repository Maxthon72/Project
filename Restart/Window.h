#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <future>
#include <semaphore>
#include <thread>
#include <fstream>




__declspec(selectany) std::binary_semaphore MainToThread{ 0 };
__declspec(selectany) std::binary_semaphore ThreadToMain{ 0 };





class Window
{
protected:
	sf::RenderWindow window;
	sf::Texture W_Texture;
	sf::Sprite W_Sprite;
	sf::Event eve;
public:
	
	virtual void Set_Texture() = 0;
	virtual void Set_Sprite() = 0;
	void W_CLose() { window.close(); }
	void W_Clear() { window.clear(); }
	void W_Display() { window.display(); }
	bool W_Open() { return window.isOpen(); }
	void W_Draw(sf::Sprite& obj) { window.draw(obj); }
	void W_Draw() { window.draw(W_Sprite); }
	bool Poll() { return window.pollEvent(eve); }
	sf::Event& Get_Eve() { return eve; }
	void Active(bool x) { window.setActive(x); }
};

