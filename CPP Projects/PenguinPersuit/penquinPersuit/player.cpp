#include "player.h"

Player::Player()
{
	Player(1,1,1);
}

Player::Player(int a_x, int a_y, char a_icon)
:m_x(a_x), m_y(a_y), m_icon(a_icon),m_nextMoveToMake(PLAYER_MOVE_NONE){}

void Player::move(int a_code)
{
	switch(a_code)
	{
	case PLAYER_MOVE_UP:
		m_y--;
		break;
	case PLAYER_MOVE_DOWN:
		m_y++;
		break;
	case PLAYER_MOVE_LEFT:
		m_x--;
		break;
	case PLAYER_MOVE_RIGHT:
		m_x++;
		break;
	}
}

int Player::getX()
{
	return m_x;
}

int Player::getY()
{
	return m_y;
}

int Player::setX(int a_value)
{
	return m_x = a_value;
}

int Player::setY(int a_value)
{
	return m_y = a_value;
}

char Player::getIcon()
{
	return m_icon;
}

char Player::setIcon(char a_icon)
{
	return m_icon = a_icon;
}

int Player::getNextMove()
{
	return m_nextMoveToMake;
}
bool Player::isAt(int a_x, int a_y)
{
	return getX() == a_x && getY() == a_y;
}

void Player::update(long a_ms)
{
	move();
}

void Player::setNextMove(int a_code)
{
	m_nextMoveToMake = a_code;
}

void Player::move()
{
	if(m_nextMoveToMake != PLAYER_MOVE_NONE)
	{
		move(m_nextMoveToMake);
		m_nextMoveToMake = PLAYER_MOVE_NONE;
	}
}
