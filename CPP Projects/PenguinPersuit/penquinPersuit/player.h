#pragma once

#define PLAYER_MOVE_NONE	0
#define PLAYER_MOVE_UP		1
#define PLAYER_MOVE_DOWN	2
#define PLAYER_MOVE_LEFT	3
#define PLAYER_MOVE_RIGHT	4
#define PLAYER_MOVE_POSIBILITIES	5

#pragma once
class Player
{
public:
	int m_x, m_y;
protected:
	char m_icon;
	int m_nextMoveToMake;
public:
	Player();
	Player(int a_x, int a_y, char a_icon);
	void move(int a_code);
	int getX();
	int getY();
	int setX(int a_value);
	int setY(int a_value);
	char getIcon();
	char setIcon(char a_icon);
	int getNextMove();
	bool isAt(int a_x, int a_y);
	virtual void update(long a_ms);
	void setNextMove(int a_code);
	void move();
};
