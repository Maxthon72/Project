#pragma once
#include <string>
#include <filesystem>

//typedef std::mt19937 MyRNG;

const static unsigned int		W = 750;
const static unsigned int		H = 750;
const static std::string		title = "Asteroids";
static std::filesystem::path	Draw = "Dr";
const static unsigned int		FPS = 30;

const static unsigned int		SW_W = 350;
const static unsigned int		SW_H = 200;
const static std::string		SW_title = "Status";

const static unsigned int		PLAYER_X = 75;
const static unsigned int		PLAYER_Y = 75;
const static unsigned int		PLAYER_MAX_SPEED = 5;
const static unsigned int		BULLET_SPEED = 5;
const static unsigned int		BULLET_LIVE = 5*FPS;
const static float				BULLET_COLL_DOWN = 0.5;
const static unsigned int		PLAYER_SPEED = 1;
const static float				PLAYER_ROT_R = 3;
const static float				PLAYER_ROT_L = -3;


const static unsigned int		SMALL_ASTEROIDE_LIVE = 1;
const static unsigned int		SMALL_OUT_OF_BIG = 2;
const static unsigned int		BIG_ASTEROIDE_LIVE = 3;
const static float				BIG_ASTEROIDE_SCALE = 1.75;
const static float				SMALL_ASTEROIDE_SCALE = 1;
const static unsigned int		SPAWNER_TIME = 4;
const static unsigned int		ASTEROIDE_SPEED = 3;