// View class
// ==========
// Singleton class that manages displaying text to the console, gathering
// user input and passing it onto ClientInterface

#pragma once

#include <iostream>
#include <string>
#include "HammurabiDataTypes.h"
#include "ClientInterface.h"

#define VIEW View::Instance()

class View
{
// member variables
private:
	OutputData	mLastTurnData;
	bool		mGameRunning;

// member functions
private:
	View(void);
	View(const View&);
	View* operator=(const View&);
	~View(void);

public:
	// draws the current state to the screen
	void Draw(InputData input);

	// shows help information about the game
	void ShowHelp(void);

	// main game loop
	void Run(void);

	// ends the game (called by the clientinterface if something went wrong)
	void EndGame(void);

	// prints a game over message before exiting
	void GameOver(void);

	// accesses the singleton
	static View* Instance();
};