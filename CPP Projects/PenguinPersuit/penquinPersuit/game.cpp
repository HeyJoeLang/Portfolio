#include <stdio.h>
#include <fstream>
#include <windows.h>
#include "game.h"
#include "commandLineInterface.h"
#include "player.h"
#include "enemy.h"

using namespace std;

/** @param the file used to generate the game world */
Game::Game(char * a_initialGameDataFile)
	// initializer list: game is running by default
	:m_running(true)
{
	currLevel = 1;
	// load map data
	m_map.load(a_initialGameDataFile);
	m_0.load("0.txt");
	m_90.load("90.txt");
	m_180.load("180.txt");
	m_270.load("270.txt");
	m_playerList.add(new Player(1, 1, 1));
	m_playerList.add(new Enemy(21, 1, 2, 200));
	m_powerUpTimeLeft = 0;
	m_powerUpLocX = 7;
	m_powerUpLocY = 2;
	timeTilRotation = 5000;
	GAME_ROTATION = DEGREES::ZERO;
}

/** @return true if the game thinks that it is running */
int Game::isRunning()
{
	return m_running;
}

/** @return a Player from the player list at the given x/y location */
Player * Game::getPlayerAt(int a_x, int a_y)
{
	Player * p;
	for(int i = 0; i < m_playerList.getSize(); ++i)
	{
		p = (Player*)m_playerList.get(i);
		if(p->isAt(a_x, a_y))
		{
			return p;
		}
	}
	return 0;
}

/** draws the game world to the win32 console */
void Game::draw()
{
	switch(GAME_ROTATION)
	{
	case  DEGREES::ZERO:
		m_directions = &m_0;
		break;
	case  DEGREES::NINETY:
		m_directions = &m_90;
		break;
	case  DEGREES::ONE_EIGHTY:
		m_directions = &m_180;
		break;
	case  DEGREES::TWO_SEVENTY:
		m_directions = &m_270;
		break;
	}
	// start the cursor at the top-left corner
	gotoxy(0, 0);
	char c;
	Player * p;
	// draw the player/enemy, and map data (in that order) at each square of the map
	for(int y = 0; y < m_map.getHeight(); ++y)
	{
		for(int x = 0; x < m_map.getWidth(); ++x)
		{
			// if there is a player/enemy here
			p = getPlayerAt(x,y);
			if(p)
			{
				// that is what we're going to draw
				setcolor(COLOR_BLACK, COLOR_GRAY);
				c = p->getIcon();
			}
			else
			{
				c = m_map.getAt(x, y);
				if(c == '#')
					setcolor(COLOR_BLUE, COLOR_BLUE);
				else if(c == '.')
					setcolor(COLOR_WHITE, COLOR_WHITE);
				else if(c == 'O')
					setcolor(COLOR_YELLOW, COLOR_BLACK);
			}
			// draw it
			printf("%c", c);
		}
		printf("\n");
	}
	
	for(int y = 0; y < m_directions->getHeight(); ++y)
	{
		gotoxy(30, 5 + y);
		for(int x = 0; x < m_directions->getWidth(); ++x)
		{
			c = m_directions->getAt(x, y);
			if(c == '#')
				setcolor(COLOR_BLUE, COLOR_BLUE);
			else if(c == '.')
				setcolor(COLOR_WHITE, COLOR_WHITE);
			else if(c == '|' || c == '-'|| c == 'W'|| c == 'A'|| c == 'S'|| c == 'D')
				setcolor(COLOR_RED, COLOR_WHITE);
			else
				setcolor(COLOR_RED, COLOR_WHITE);
			printf("%c", c);
		}
		printf("\n");
	}
}

int Game::translateKeyPressToMove(char a_keyPress)
{
	// 'w', 'a', 's', and 'd' are used to move the player
	switch(GAME_ROTATION)
	{
	case  DEGREES::ZERO:
		switch(a_keyPress)
		{
		case 'w':	return PLAYER_MOVE_UP;
		case 'a':	return PLAYER_MOVE_LEFT;
		case 's':	return PLAYER_MOVE_DOWN;
		case 'd':	return PLAYER_MOVE_RIGHT;
		}
		return PLAYER_MOVE_NONE;
	case  DEGREES::NINETY:
		switch(a_keyPress)
		{
		case 'w':	return PLAYER_MOVE_RIGHT;
		case 'a':	return PLAYER_MOVE_UP;
		case 's':	return PLAYER_MOVE_LEFT;
		case 'd':	return PLAYER_MOVE_DOWN;
		}
		return PLAYER_MOVE_NONE;
	case  DEGREES::ONE_EIGHTY:
		switch(a_keyPress)
		{
		case 'w':	return PLAYER_MOVE_DOWN;
		case 'a':	return PLAYER_MOVE_RIGHT;
		case 's':	return PLAYER_MOVE_UP;
		case 'd':	return PLAYER_MOVE_LEFT;
		}
		return PLAYER_MOVE_NONE;
	case  DEGREES::TWO_SEVENTY:
		switch(a_keyPress)
		{
		case 'w':	return PLAYER_MOVE_LEFT;
		case 'a':	return PLAYER_MOVE_DOWN;
		case 's':	return PLAYER_MOVE_RIGHT;
		case 'd':	return PLAYER_MOVE_UP;
		}
		return PLAYER_MOVE_NONE;
	}
}

/** @param a_keyPress key that will move the player */
void Game::handleInput(char a_keyPress)
{
	switch(a_keyPress)
	{
	case 27:	case 'q':	m_running = false;	 break;
	case ']':	rotateMap();		break;
	default:
			Player * p = (Player*)m_playerList.get(0);
			p->setNextMove(translateKeyPressToMove(a_keyPress));
		break;
	}
}
void Game::rotateMap()
{
	Player * p = (Player*)m_playerList.get(0);
	Enemy * e = (Enemy*)m_playerList.get(1);
	int rotationSelection = rand() % 3 + 1;

	switch(rotationSelection)
	{
	case 1:

		m_map.setAt(p->getX(), p->getY(),p->getIcon());
		m_map.setAt(e->getX(), e->getY(),e->getIcon());

		m_map.flipCCW();

		p->setX(m_map.getCharXPos(p->getIcon())); 
		p->setY(m_map.getCharYPos(p->getIcon())); 
		e->setX(m_map.getCharXPos(e->getIcon())); 
		e->setY(m_map.getCharYPos(e->getIcon())); 

		m_map.setAt(p->getX(), p->getY(), '.');
		m_map.setAt(e->getX(), e->getY(), '.');

		break;
	case 2:
		m_map.setAt(p->getX(), p->getY(),p->getIcon());
		m_map.setAt(e->getX(), e->getY(),e->getIcon());

		m_map.flipCW();

		p->setX(m_map.getCharXPos(p->getIcon())); 
		p->setY(m_map.getCharYPos(p->getIcon())); 
		e->setX(m_map.getCharXPos(e->getIcon())); 
		e->setY(m_map.getCharYPos(e->getIcon())); 

		m_map.setAt(p->getX(), p->getY(), '.');
		m_map.setAt(e->getX(), e->getY(), '.');
		break;
	case 3:
		break;
	}
	if(m_map.getAt(11,1) == 'O')
		GAME_ROTATION = DEGREES::ZERO;
	else if(m_map.getAt(1,11) == 'O')
		GAME_ROTATION = DEGREES::TWO_SEVENTY;
	else if(m_map.getAt(11,21) == 'O')
		GAME_ROTATION = DEGREES::ONE_EIGHTY;
	else if(m_map.getAt(21,11) == 'O')
		GAME_ROTATION = DEGREES::NINETY;
}
/** @param a_ms timse (in milliseconds) since the last update. updates the game logic */
void Game::update(int a_ms)
{
	Player * p;
	Enemy * e;

	for(int i = 0; i < m_playerList.getSize(); ++i)
	{
		p = (Player*)m_playerList.get(i);
		
		if(p != (Player*)m_playerList.get(0))
		{
			e = (Enemy*)p;
			if(m_powerUpTimeLeft > 0)
				e->setIcon(1);
			else
				e->setIcon(2);
			e->ai(a_ms);
		}

		int nextMove = p->getNextMove();

		if(nextMove == PLAYER_MOVE_UP && (p->getY() <= 0 || m_map.getAt(p->getX(),p->getY()-1) == '#'))
			p->setNextMove(PLAYER_MOVE_NONE); 
		if(nextMove == PLAYER_MOVE_DOWN && (p->getY() >= m_map.getHeight() - 1 || m_map.getAt(p->getX(),p->getY()+1) == '#'))
			p->setNextMove(PLAYER_MOVE_NONE);
		if(nextMove == PLAYER_MOVE_LEFT && (p->getX() <= 0 || m_map.getAt(p->getX() - 1, p->getY()) == '#'))
			p->setNextMove(PLAYER_MOVE_NONE);
		if(nextMove == PLAYER_MOVE_RIGHT && (p->getX() >= m_map.getWidth() - 1 || m_map.getAt(p->getX() + 1,p->getY()) == '#'))
			p->setNextMove(PLAYER_MOVE_NONE);

		if(p != (Player*)m_playerList.get(0))
			e->move();
		else
			p->update(a_ms);

		if(m_map.getAt(p->getX(),p->getY()) == 'O')
		{
			if(p == (Player*)m_playerList.get(0))
				m_running = -1;
			else if(p == (Player*)m_playerList.get(1))
				m_running = -2;

		}
	}
	timeTilRotation -= a_ms;
	if(timeTilRotation <= 0)
	{
		rotateMap();
		int rotationTime = rand() % 6 + 1;
		timeTilRotation += rotationTime * 1000;
	}

}

/** a destructor to clean up game data after the game finishes runtime */
Game::~Game()
{
	// no data is dynamically allocated, so nothing needs to be cleaned up
}
