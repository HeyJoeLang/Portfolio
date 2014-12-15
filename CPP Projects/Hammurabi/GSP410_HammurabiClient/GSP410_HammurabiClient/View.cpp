#include "View.h"

// function declarations for string manipulation
double cnvtToNumber(const std::string &num);
std::string &trim(std::string &str);

double cnvtToNumber(const std::string &num)
{
	char * ptr;
	double toret = strtod( num.c_str(), &ptr);

	if (*ptr != 0)
	{
		// throw an error
	}

	return toret;
}

std::string &trim(std::string &str)
{
	// remove trailing spaces
	if (str.length() > 0)
	{
		unsigned int pos = str.length() - 1;

		while (str[pos] == ' ')
		{
			--pos;
		}

		if (pos < (str.length() - 1) )
		{
			str.erase(pos + 1);
		}

		// remove spaces at the beginning
		pos = 0;

		while (str[pos] == ' ')
		{
			++pos;
		}

		if (pos > 1)
		{
			str.erase(0, pos);
		}
	}

	return str;
}

View::View(void)
{
	// assume the game is running until otherwise notified
	mGameRunning = true;
	
}

View::~View(void)
{
}

View::View(const View &mm)
{
}

View* View::operator=(const View &mm)
{
	return this;
}

View* View::Instance()
{
	static View instance;

	return &instance;
}

void View::Run()
{
	// connect the client and get the initial game state
	mLastTurnData = CLIENTINTERFACE->ConnectToServer();

	// main game loop
	while(mGameRunning)
	{
		// check the data from the previous turn to verify if the game has ended
		if (mLastTurnData.overthrown || mLastTurnData.performanceRating > 0)
		{
			GameOver();
		}

		InputData input;

		input.numAcresPurchased = 0;
		input.numBushelsFed = 0;
		input.numBushelsPlanted = 0;
		input.resetGame = false;

		// print the game state to the screen
		// don't draw if we're quitting (looks weird when it resets as its shutting down)
		if (mGameRunning)
			Draw(input);

		// get first input (num acres purchased)
		// check if the user wants to quit/restart, or entered
		// an invalid input, else set the value
		std::string userInput;
		bool verified = false;
		
		while (!verified && !input.resetGame && mGameRunning)
		{

			std::cout << "Restart (r). Quit (q). Help (h). Redraw current state (d)." << std::endl << std::endl;
			std::cout << "Enter the number of acres to purchase/sell: (" << -mLastTurnData.acresOwned << " to " << mLastTurnData.bushelsLeft / mLastTurnData.bushelsPerAcre << ")" << std::endl << "Use negative numbers to sell." << std::endl;
			
			
			std::getline( std::cin, userInput);

			userInput = trim(userInput);

			if (userInput.length() > 0)
			{
				if (userInput[0] == 'r' || userInput[0] == 'R')
				{
					// restart
					std::cout << "restart" << std::endl;
					input.resetGame = true;
					break;
				}
				else if (userInput[0] == 'q' || userInput[0] == 'Q')
				{
					// quit
					std::cout << "quit" << std::endl;
					mGameRunning = false;
					break;
				}
				else if (userInput[0] == 'h' || userInput[0] == 'H')
				{
					ShowHelp();
				}
				else if (userInput[0] == 'd' || userInput[0] == 'D')
				{
					Draw(input);
				}
				else
				{
					int num = cnvtToNumber(userInput);

					if (num >= -mLastTurnData.acresOwned && num <= mLastTurnData.bushelsLeft / mLastTurnData.bushelsPerAcre)
					{
						if (num < 0)
						{
							std::cout << "You just sold " << -num << " acres for " << -num * mLastTurnData.bushelsPerAcre << " bushels" << std::endl << std::endl;
						}
						else if (num > 0)
						{
							std::cout << "You just purchased " << num << " acres for " << num * mLastTurnData.bushelsPerAcre << " bushels" << std::endl << std::endl;
						}
						else
						{
							std::cout << "You will purchase/sell no acres this turn" << std::endl << std::endl;
						}

						input.numAcresPurchased = num;
						verified = true;
					}
					else
					{
						std::cout << "Incorrect input! Out of the valid range or not an instruction." << std::endl << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Incorrect input! Out of the valid range or not an instruction." << std::endl << std::endl;
			}
		}
		
		// keep checking for input if the user didn't input the correctly, didn't reset and didn't quit

		verified = false;

		// get the second input (num bushels fed)
		// check if the user wants to quit/restart, or entered
		// an invalid input, else set the value
		while (!verified && !input.resetGame && mGameRunning)
		{
			std::cout << "Restart (r). Quit (q). Help (h). Redraw current state (d)." << std::endl << std::endl;
			std::cout << "Enter the number of bushels to feed to the population: (0 to " << mLastTurnData.bushelsLeft - (mLastTurnData.bushelsPerAcre * input.numAcresPurchased) << ")" << std::endl;
						
			std::getline( std::cin, userInput);

			userInput = trim(userInput);

			if (userInput.length() > 0)
			{
				if (userInput[0] == 'r' || userInput[0] == 'R')
				{
					// restart
					std::cout << "restart" << std::endl;
					input.resetGame = true;
					break;
				}
				else if (userInput[0] == 'q' || userInput[0] == 'Q')
				{
					// quit
					std::cout << "quit" << std::endl;
					mGameRunning = false;
					break;
				}
				else if (userInput[0] == 'h' || userInput[0] == 'H')
				{
					ShowHelp();
				}
				else if (userInput[0] == 'd' || userInput[0] == 'D')
				{
					Draw(input);
				}
				else
				{
					int num = cnvtToNumber(userInput);

					if (num >= 0 && num <= (mLastTurnData.bushelsLeft - (mLastTurnData.bushelsPerAcre * input.numAcresPurchased)))
					{
						std::cout << std::endl;
						input.numBushelsFed = num;
						verified = true;
					}
					else
					{
						std::cout << "Incorrect input! Out of the valid range or not an instruction." << std::endl << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Incorrect input! Out of the valid range or not an instruction." << std::endl << std::endl;
			}
		}

		// keep checking for input if the user didn't input the correctly, didn't reset and didn't quit

		verified = false;

		// get the third input (num bushels planted)
		// check if the user wants to quit/restart, or entered
		// an invalid input, else set the value
		while (!verified && !input.resetGame && mGameRunning)
		{
			std::cout << "Restart (r). Quit (q). Help (h). Redraw current state (d)." << std::endl << std::endl;
			// pick the lowest value of the three
			std::cout << "Enter the number of bushels to plant (1 person can plant 10 bushels on 10 acres): (0 to " << min(min((mLastTurnData.acresOwned + input.numAcresPurchased), mLastTurnData.totalPopulation * 10), mLastTurnData.bushelsLeft - input.numBushelsFed - (input.numAcresPurchased * mLastTurnData.bushelsPerAcre)) << ")" << std::endl;
						
			std::getline( std::cin, userInput);

			userInput = trim(userInput);

			if (userInput.length() > 0)
			{
				if (userInput[0] == 'r' || userInput[0] == 'R')
				{
					// restart
					std::cout << "restart" << std::endl;
					input.resetGame = true;
					break;
				}
				else if (userInput[0] == 'q' || userInput[0] == 'Q')
				{
					// quit
					std::cout << "quit" << std::endl;
					mGameRunning = false;
					break;
				}
				else if (userInput[0] == 'h' || userInput[0] == 'H')
				{
					ShowHelp();
				}
				else if (userInput[0] == 'd' || userInput[0] == 'D')
				{
					Draw(input);
				}
				else
				{
					int num = cnvtToNumber(userInput);

					// pick the lowest value of the three
					if (num >= 0 && num <= min(min((mLastTurnData.acresOwned + input.numAcresPurchased), mLastTurnData.totalPopulation * 10), mLastTurnData.bushelsLeft - input.numBushelsFed - (input.numAcresPurchased * mLastTurnData.bushelsPerAcre)))
					{
						std::cout << std::endl;
						input.numBushelsPlanted = num;
						verified = true;
					}
					else
					{
						std::cout << "Incorrect input! Out of the valid range or not an instruction." << std::endl << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Incorrect input! Out of the valid range or not an instruction." << std::endl << std::endl;
			}
		}
		
		// keep checking for input if the user didn't input the correctly, didn't reset and didn't quit

		bool commit = false;
		verified = false;

		Draw(input);

		while (!verified && mGameRunning && !input.resetGame)
		{
			std::cout << "Restart (r). Quit (q). Help (h). Redraw current state (d)." << std::endl << std::endl;
			std::cout << "Do you wish to commit these values and calculate the next turn? (y/n)" << std::endl;
			std::getline( std::cin, userInput);

			userInput = trim(userInput);

			if (userInput.length() > 0)
			{

				if (userInput[0] == 'r' || userInput[0] == 'R')
				{
					// restart
					std::cout << "restart" << std::endl;
					input.resetGame = true;
					break;
				}
				else if (userInput[0] == 'q' || userInput[0] == 'Q')
				{
					// quit
					std::cout << "quit" << std::endl;
					mGameRunning = false;
					break;
				}
				else if (userInput[0] == 'h' || userInput[0] == 'H')
				{
					ShowHelp();
				}
				else if (userInput[0] == 'd' || userInput[0] == 'D')
				{
					Draw(input);
				}
				else if (userInput[0] == 'y' || userInput[0] == 'Y')
				{
					std::cout << std::endl;
					verified = true;
					commit = true;
					break;
				}
				else if (userInput[0] == 'n' || userInput[0] == 'N')
				{
					std::cout << std::endl;
					verified = true;
					break;
				}
				else
				{
					std::cout << "Incorrect input! Not an instruction." << std::endl << std::endl;
				}
			}
			else
			{
				std::cout << "Incorrect input! Not an instruction." << std::endl << std::endl;
			}

		}

		// verify if the user wants to commit.
		// if not, go back to the start
		// else, send input to the server and wait
		if (commit || input.resetGame)
		{
			mLastTurnData = CLIENTINTERFACE->SendToServer(input);
		}
	}

	// shutdown the ClientInterface
	CLIENTINTERFACE->ShutDown();
}

// ends the game (called by the clientinterface if something went wrong)
void View::EndGame(void)
{
	mGameRunning = false;
}

// draws the current game state to the screen
void View::Draw(InputData current)
{
	// clear the screen
	system("cls");

	// print the current game state
	std::cout << "Hammurabi by Chris Dickinson and Joe Lang" << std::endl;
	std::cout << "=========================================" << std::endl;
	std::cout << "Current Year: " << mLastTurnData.currentYear << std::endl;
	std::cout << "Total Population: " << mLastTurnData.totalPopulation << ", " << mLastTurnData.numPopStarved << " people starved, and " << mLastTurnData.numImmigrants << " people immigrated to the city." << std::endl;
	std::cout << "Total % population starved so far: " << mLastTurnData.percentPopDiedOverall << std::endl;
	
	// only print plague information if a plague happened
	if (mLastTurnData.numDiedToPlague > 0)
	{
		if (mLastTurnData.numDiedToPlague == 1)
		{
			std::cout << mLastTurnData.numDiedToPlague << " person died to plague. Poor guy." << std::endl;
		}
		else
		{
			std::cout << mLastTurnData.numDiedToPlague << " people died to plague!" << std::endl;
		}
	}

	std::cout << "The city owns " << mLastTurnData.acresOwned << " acres." << std::endl;
	std::cout << "You harvested " << mLastTurnData.bushelsHarvestedPerAcre << " bushels per acre." << std::endl;
	std::cout << "Rats ate " << mLastTurnData.bushelsEatenByRats << " bushels." << std::endl;
	std::cout << "You currently have " << mLastTurnData.bushelsLeft << " bushels in stock." << std::endl;
	std::cout << "Land is currently trading at " << mLastTurnData.bushelsPerAcre << " bushels per acre." << std::endl;
	
	// print the current input
	std::cout << std::endl;
	std::cout << "Number of acres to buy this turn: " << current.numAcresPurchased << std::endl;
	std::cout << "Number of bushels to feed to people this turn: " << current.numBushelsFed << std::endl;
	std::cout << "Number of bushels to plant this turn: " << current.numBushelsPlanted << std::endl << std::endl;
}

// shows help info
void View::ShowHelp(void)
{
	std::cout << std::endl << "Try your hand at governing ancient sumeria successfully, for a 10-year"		<< std::endl <<	"term of office." << std::endl << std::endl;
	std::cout << "The Rules:" << std::endl;
	std::cout << "  1. The game lasts 10 years, with a year being one turn." << std::endl;
	std::cout << "  2. Each year, enter how many bushels of grain to allocate to buying (or"	<< std::endl << "     selling) acres of land, feeding your population and planting crops" << std::endl << "     for the next year" << std::endl;
	std::cout << "  3. Each person needs 20 bushels of grain each year to live and can"			<< std::endl << "     till at most 10 acres of land." << std::endl;
	std::cout << "  4. Each acre of land requires one bushel of grain to plant seeds."			<< std::endl;
	std::cout << "  5. The price of each acre of land fluctuates from 17 bushels per acre"		<< std::endl << "     to 26 bushels." << std::endl;
	std::cout << "  6. If the conditions in your country ever become bad enough, the people"	<< std::endl << "     will overthrow you and you won't finish your 10-year term." << std::endl;
	std::cout << "  7. If you make it to the 11th year, your rule will be evaluated and"		<< std::endl << "     you'll be ranked against great figures in history!" << std::endl;
	std::cout << std::endl << "Press the enter key to continue..." << std::endl;

	// get input, but then clear the buffer
	std::cin.get();
	std::cin.clear();
}

// prints a game over message to the screen before exiting
void View::GameOver(void)
{
	system("cls");

	srand(time(NULL)); // seed the RNG if the player loses and gets the assassination performance rating

	if (mLastTurnData.overthrown)
	{
		std::cout << "You let too many people starve in a single turn!" << std::endl << std::endl;
		mLastTurnData.performanceRating = 1;
	}

	// generic information
	std::cout << "In your " << mLastTurnData.currentYear - 1 << "-year term of office, " << mLastTurnData.percentPopDiedOverall << "% of the population starved." << std::endl;
	if (mLastTurnData.totalPopulation > 0)
	{
		std::cout << "You started with 10 acres per person, and ended with " << mLastTurnData.acresOwned / mLastTurnData.totalPopulation << " acres per person." << std::endl << std::endl;
	}
	else
	{
		std::cout << "You killed literally everyone, you heartless beast!" << std::endl << std::endl;
	}

	// performance-based messages
	switch(mLastTurnData.performanceRating)
	{
	case 0:
		std::cout << "Error: This should not happen!!" << std::endl;
		break;

	case 1:
		std::cout << "Due to this extreme mismanagement you have not only been impeached and"	<< std::endl << "thrown out of office, but you have also been declared 'national fink'!" << std::endl;
		break;

	case 2:
		std::cout << "Your heavy-handed performance smacks of Nero and Ivan IV. The people"		<< std::endl << "(remaining) find you an unpleasant ruler, and, frankly, hate your guts!" << std::endl;
		break;

	case 3:
		std::cout << "Your performance could have been somewhat better, but really wasn't"		<< std::endl << "too bad at all. " << (int)(mLastTurnData.totalPopulation*(float(rand() % 8) / 10.0f)) << " people would dearly like to see you assassinated, but" << std::endl << "we all have our trivial problems." << std::endl;
		break;

	case 4:
		std::cout << "A fantastic performance! Charlemange, Disraeli, and Jefferson combined"	<< std::endl << "could not have done better!" << std::endl;
		break;

	default:
		std::cout << "Error: This should not happen!!" << std::endl;
		break;
	}

	bool verified = false;

	while (!verified)
	{
		std::cout << std::endl << "Do you wish to restart? (y/n)" << std::endl;

		string userInput;

		std::getline( std::cin, userInput);

		userInput = trim(userInput);

		if (userInput.length() > 0)
		{
			if (userInput[0] == 'n' || userInput[0] == 'N')
			{
				// stop the game
				mGameRunning = false;
				verified = true;
			}
			else if (userInput[0] == 'y' || userInput[0] == 'Y')
			{
				// restart the game
				InputData in;
				in.numAcresPurchased = 0;
				in.numBushelsFed = 0;
				in.numBushelsPlanted = 0;
				in.resetGame = true;
				mLastTurnData = CLIENTINTERFACE->SendToServer(in);
				verified = true;
			}
			else
			{
				std::cout << "Incorrect input! Not an instruction." << std::endl << std::endl;
			}
		}
		else
		{
			std::cout << "Incorrect input! Not an instruction." << std::endl << std::endl;
		}
	}
}