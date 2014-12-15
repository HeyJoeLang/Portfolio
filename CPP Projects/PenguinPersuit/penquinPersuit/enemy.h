#pragma once 
#include "player.h"

class Enemy : public Player
{
private:
	long m_howLongSinceLastMove;
	long m_howLongToWaitBetweenMoves;
public:
	void ai(long ms);
	Enemy(int a_x, int a_y, char a_icon, long a_speed);
	void update(long a_ms);
	void setSpeed(long a_ms);
	int getRandomMove();
};
