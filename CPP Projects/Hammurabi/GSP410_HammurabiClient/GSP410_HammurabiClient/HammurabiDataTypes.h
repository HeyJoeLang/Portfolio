// Data types and structs used in Hammurabi

#pragma once

struct InputData
{
	int numAcresPurchased;
	int numBushelsFed;
	int numBushelsPlanted;
	bool resetGame;
};

struct OutputData
{
	int currentYear;
	int totalPopulation;
	int numPopStarved;
	int numImmigrants;
	int acresOwned;
	int bushelsHarvestedPerAcre;
	int bushelsEatenByRats;
	int bushelsLeft;
	int bushelsPerAcre;
	int numDiedToPlague;
	bool overthrown;
	float percentPopDiedOverall;
	int performanceRating;
};