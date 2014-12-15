#pragma once
#include "vectr.h"
#include "map.h"
#include "player.h"
#include "enemy.h"

class Game
{
private:
	enum DEGREES
	{
		ZERO,
		NINETY,
		ONE_EIGHTY,
		TWO_SEVENTY
	};
	int currLevel;
	DEGREES GAME_ROTATION;
	map m_map;
	map m_0, m_90, m_180, m_270;
	map * m_directions;
	int m_running;
	Vectr m_playerList;
	float m_powerUpTimeLeft;
	int m_powerUpLocX, m_powerUpLocY;
	int translateKeyPressToMove(char a_keyPress);
	int timeTilRotation;
public:
	int getCurrLevel(){return currLevel;}
	Game(char * a_initialGameDataFile);
	int isRunning();
	void draw();
	void rotateMap();
	void handleInput(char a_keyPress);
	void update(int a_ms);
	Player * getPlayerAt(int a_x, int a_y);
	~Game();
};