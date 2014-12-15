#include "enemy.h"
#include <stdlib.h>

Enemy::Enemy(int a_x, int a_y, char a_icon, long a_speed)
:Player(a_x,a_y,a_icon),m_howLongToWaitBetweenMoves(a_speed),m_howLongSinceLastMove(0)
{}

void Enemy::update(long a_ms)
{
	ai(a_ms);
	move();
}

void Enemy::ai(long a_ms)
{
	m_howLongSinceLastMove += a_ms;
	if(m_howLongSinceLastMove > m_howLongToWaitBetweenMoves)
	{
		setNextMove(getRandomMove());
		m_howLongSinceLastMove -= m_howLongToWaitBetweenMoves;
	}
}

void Enemy::setSpeed(long ms)
{
	m_howLongToWaitBetweenMoves = ms;
	m_howLongSinceLastMove = 0;
}

int Enemy::getRandomMove()
{
	return rand() % PLAYER_MOVE_POSIBILITIES;
}
