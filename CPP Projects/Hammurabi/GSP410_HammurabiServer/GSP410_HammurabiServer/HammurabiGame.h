// GSP410 Chris Dickinson & Joe Lang
// Hammurabi Game class

#pragma once

#include "time.h"
#include <iostream>
#include "HammurabiDataTypes.h"

class HammurabiGame
{
private:
	OutputData mCurrentState;
	int			mTotalLived;
	int			mTotalKilled;

public:
	HammurabiGame(void);
	~HammurabiGame(void);

	OutputData ProcessTurn(InputData input);
};