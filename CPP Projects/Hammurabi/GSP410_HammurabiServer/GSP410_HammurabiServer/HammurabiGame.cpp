#include "HammurabiGame.h"

HammurabiGame::HammurabiGame()
{
	// seed the RNG
	srand(time(NULL));
}

HammurabiGame::~HammurabiGame()
{


}

// processes the next turn and returns output data back
// to the calling object (usually ServerInterface)
OutputData HammurabiGame::ProcessTurn(InputData input)
{
	

	// create an OutputData object to store results
	OutputData output;

	// if the resetGame flag is set, just return the defaults
	if (input.resetGame)
	{
		output.acresOwned = 1000;
		output.bushelsEatenByRats = 200;
		output.bushelsHarvestedPerAcre = rand() % 5 + 1;
		output.bushelsLeft = 2800;
		output.bushelsPerAcre = 17 + (rand() % 9 + 1);
		output.currentYear = 1;
		output.numDiedToPlague = 0;
		output.numImmigrants = 5;
		output.numPopStarved = 0;
		output.overthrown = false;
		output.percentPopDiedOverall = 0;
		output.totalPopulation = 100;
		output.performanceRating = 0;

		mTotalLived = 100;
		mTotalKilled = 0;

		mCurrentState = output;
		return output;
	}

	// assume the player hasn't been overthrown, unless we set it in the next block
	output.overthrown = false;

	// find out how many people starved
	int peopleFed = int(input.numBushelsFed / 20);
	output.numPopStarved = 0;
	if(mCurrentState.totalPopulation > peopleFed)
	{
		output.numPopStarved = mCurrentState.totalPopulation - peopleFed;
		if(output.numPopStarved > int((45 * mCurrentState.totalPopulation) / 100))
			output.overthrown = true;
	}
	
	mTotalKilled += output.numPopStarved;

	//output.percentPopDiedOverall = ((mCurrentState.currentYear - 1) * mCurrentState.percentPopDiedOverall + (output.numPopStarved * 100	/ mCurrentState.totalPopulation)) / mCurrentState.currentYear;

	output.totalPopulation = mCurrentState.totalPopulation - output.numPopStarved;

	//First, add the immigrants, then check for the plague
	// get the population growth
	int r = (rand() % 5) + 1;
	output.numImmigrants = int(((r * ( 20 * mCurrentState.acresOwned + mCurrentState.bushelsLeft) / mCurrentState.totalPopulation) / 100) + 1);
	output.totalPopulation += output.numImmigrants;

	mTotalLived += output.numImmigrants;

	output.percentPopDiedOverall = ((float)mTotalKilled / (float)mTotalLived) * 100.0f;

	// check if a plague occurred
	int plagueProb = rand() % 100 + 1;
	if(plagueProb <= 15)
	{
		output.numDiedToPlague = output.totalPopulation / 2;
		output.totalPopulation *= 0.5;
	}
	
	//bushels per acre tade rade
	output.bushelsPerAcre = (rand() % 10) + 17;

	//acres bought or sold
	output.acresOwned = mCurrentState.acresOwned + input.numAcresPurchased;
	output.bushelsLeft = mCurrentState.bushelsLeft - (input.numAcresPurchased * mCurrentState.bushelsPerAcre);
		
	//bushels harvested per acre
	output.bushelsHarvestedPerAcre = (rand() % 5) + 1;

	//bushels harvested
	output.bushelsLeft -= input.numBushelsPlanted / 2;
	int harvested = input.numBushelsPlanted * output.bushelsHarvestedPerAcre;

	//rats
	int ratChance = rand() % 5 + 1;
	output.bushelsEatenByRats = 0;
	if(ratChance == 1 || ratChance == 3 || ratChance == 5)
		output.bushelsEatenByRats = output.bushelsLeft / ratChance;
	output.bushelsLeft -= output.bushelsEatenByRats;
	output.bushelsLeft += harvested;
	
	output.currentYear = mCurrentState.currentYear + 1;

	int acresPerPerson = 0;
	
	if (output.totalPopulation > 0)
		acresPerPerson = output.acresOwned / output.totalPopulation;

	//end game if year exceeds 10
	if(output.currentYear > 10)
	{
		if(output.percentPopDiedOverall > 33 || acresPerPerson < 7)
			output.performanceRating = 1;
		else if(output.percentPopDiedOverall > 10 || acresPerPerson < 9)
			output.performanceRating = 2;
		else if(output.percentPopDiedOverall > 3  || acresPerPerson < 10)
			output.performanceRating = 3;
		else
			output.performanceRating = 4;
	}
	else
	{
		output.performanceRating = 0;
	}
	
	// set the current state to the new output
	mCurrentState = output;

	return output;

}