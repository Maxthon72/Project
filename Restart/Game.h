#pragma once
#include "Main_Window.h"
#include "Status_Window.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroide.h"
#include <thread>
#include <vector>
#include <filesystem>
#include <regex>
#include <future>
#include <fstream>
#include <random>
class Game
{

	sf::Clock shoot;
	sf::Clock asteroide;
	sf::Clock timer;
	sf::Clock score_clock;
	sf::Clock Player_colision;
	Main_Window MW;
	Player* MP;
	Status_Window SW;
	Status_Window* Status_window_point;
	std::vector<sf::Texture*> Asteroid_Texture;
	std::vector<Bullet*> Bullets;
	std::vector<Smal_Asteroid*> Small_Asteroids;
	std::vector<Big_Asteroid*> Big_Asteroids;
	int state;
	int score;
	int n_asteroide;
	std::future<std::vector<sf::Texture*>> fu;
	std::ofstream MyFile;
	std::default_random_engine randomEngine;

public:
	Game();
	int GEt_Random(int x);
	void Create_SW_Thread();
	void MG_Loop();
	void SG_Event_Loop();
	void MG_Event_Loop();
	void GG_Event_Loop();
	void Enemy_Spawn();
	void Spawn_Small_Asteroide(int);
	void Spawn_Small_Asteroide(Big_Asteroid*);
	void Spawn_Big_Asteroide(int);
	sf::Texture* Get_Random_Texture();
	void Clean();
	void Reset();
	bool Check_GG();
	void Save();
	bool Colision(sf::Sprite&, sf::Sprite&);
};

