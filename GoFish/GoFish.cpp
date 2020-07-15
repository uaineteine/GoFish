// GoFish.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Player.h"
#include <time.h>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>

//create players where first player is player[0];
vector<Player> Players;
int PlayerCount = 4;

//The Deck in the centre-all 52 cards
vector<Card> TheDeck;

//Decksize
int DeckSize = 52;

//SaveGameName
string SaveFileName;
string DefaultSaveName = "autosave.txt";

//default allAI is true
bool allAI = true;

void CentreString(char* input)
{
	int l = strlen(input);
	int pos = (int)((80 - l) / 2);
	for (int i = 0; i<pos; i++)
		cout << " ";

	cout << input << endl;
}
void ShuffleDeck(int shuffleCount)
{
	for (int i = 0; i < shuffleCount; i ++)
		std::random_shuffle(TheDeck.begin(), TheDeck.end());
}
void PrintGame()
{
	//print at least the two player names
	stringstream printStr;
	printStr << Players[0].Name << " Cards(" <<
		Players[0].PlayerCards.size() << ") Points(" <<
		Players[0].Points << ")";
	string ToPrint = printStr.str();

	char *cstr = &ToPrint[0u];
	CentreString(cstr);

	//gap
	for (int i = 0; i < 6; i++)
	{
		cout << endl;
	}

	//deck and players 3-4
	string Deck = to_string(DeckSize);
	Deck.append(" cards");
	string CentreLine;
	//extra players to print
	if (PlayerCount > 2)
	{
		CentreLine.append(" ");

		stringstream printStr3;
		printStr3 << Players[2].Name << " Cards(" <<
			Players[2].PlayerCards.size() << ") Points(" <<
			Players[2].Points << ")";
		CentreLine.append(printStr3.str());

		int gap = 35 - printStr3.str().length();
		for (int i = 0; i < gap; i++)
			CentreLine.append(" ");;
		CentreLine.append(Deck);
		if (PlayerCount == 4)
		{
			stringstream printStr4;
			printStr4 << Players[3].Name << " Cards(" <<
				Players[3].PlayerCards.size() << ") Points(" <<
				Players[3].Points << ")";
			gap = 36 - printStr4.str().length();
			for (int i = 0; i < gap; i++)
				CentreLine.append(" ");;
			CentreLine.append(printStr4.str());
		}
	}
	else
	{
		int gap = 36;
		for (int i = 0; i < gap; i++)
			CentreLine.append(" ");;
		CentreLine.append(Deck);
	}
	cout << CentreLine << endl;

	//gap
	for (int i = 0; i < 6; i++)
	{
		cout << endl;
	}

	//print at least the two player names
	stringstream printStr2;
	printStr2 << Players[1].Name << " Cards(" <<
		Players[1].PlayerCards.size() << ") Points(" <<
		Players[1].Points << ")";
	ToPrint = printStr2.str();

	cstr = &ToPrint[0u];
	CentreString(cstr);

	cout << endl;
}
//Gather all the cards as an appended list
string GetCardString(int currentPlayer)
{
	string output = "";
	for (int i = 0; i < Players[currentPlayer].PlayerCards.size(); i++)
	{
		//Append the digit or A, J, Q, K if num > 10
		switch (Players[currentPlayer].PlayerCards[i].Num)
		{
		case 1:
			output.append("A");
			break;
		case 11:
			output.append("J");
			break;

		case 12:
			output.append("Q");
			break;

		case 13:
			output.append("K");
			break;

		default:
			output.append(to_string(Players[currentPlayer].PlayerCards[i].Num));
			break;
		}
		//Append the suit
		output.append("(");
		switch (Players[currentPlayer].PlayerCards[i].Suit)
		{
		case 0:
			output.append("H");
			break;
		case 1:
			output.append("S");
			break;

		case 2:
			output.append("C");
			break;

		case 3:
			output.append("D");
			break;
		}
		output.append("), ");
	}
	return output;
}
/*Function that attempts to take from another player
(0 based index) and give to the current player (0 based index)*/
bool AttemptSteal(int currPlayer, int StealFrom, string CardToSteal)
{
	bool match = false;
	int matchPos;
	for (int k = 0; k < Players[StealFrom].PlayerCards.size(); k++)
	{
		if (to_string(Players[StealFrom].PlayerCards[k].Num) == CardToSteal)
		{
			match = true;
			matchPos = k;
			break;
		}
	}
	if (match == true)
	{
		//Steal that card
		Players[currPlayer].AddCard(Players[StealFrom].PlayerCards[matchPos]);
		//remove from the other player
		Players[StealFrom].RemoveCardByIndex(matchPos);
		//success
		if (Players[currPlayer].AI == false)
		{
			string PrintString = CardToSteal;
			if (CardToSteal == "1")
				PrintString = "A";
			else if (CardToSteal == "11")
				PrintString = "J";
			else if (CardToSteal == "12")
				PrintString = "Q";
			else if (CardToSteal == "13")
				PrintString = "K";
			cout << "You have stolen a " << PrintString << " from " << Players[StealFrom].Name << endl;
		}
		return true;
	}
	else
	{
		//return false, the player must gofish
		return false;
	}
}
//Player will go and draw from the deck
void PlayerGoFish(int currPlayer)
{
	if (DeckSize > 0)
	{
		if (Players[currPlayer].AI == false)
		{
			cout << "They do not have one, Go Fish!" << endl;
			system("pause");
		}
		//removed cin;
		Card cardToAdd = TheDeck[0];
		Players[currPlayer].AddCard(cardToAdd);
		TheDeck.erase(TheDeck.begin());
		DeckSize -= 1;
		if (Players[currPlayer].AI == false)
		{
			string PrintStr;
			switch (cardToAdd.Num)
			{
			case 1: 
				PrintStr = "A";
				break;
			case 11:
				PrintStr = "J";
				break;
			case 12:
				PrintStr = "Q";
				break;
			case 13:
				PrintStr = "K";
				break;
			default:
				PrintStr = to_string(cardToAdd.Num);
				break;
			}
			cout << "You have drawn " << cardToAdd.Num << " (" << cardToAdd.Suit << ")" << endl;
		}
	} 
	else cout << "The deck is empty!" << endl;
}
//Return 0 based index integers of winning players
vector<int> WhoWon()
{
	int TopPlayer = 0; //default
	for (int i = 1; i < PlayerCount; i++)
	{
		//check and replace with any player with a higher value
		if (Players[i].Points > Players[TopPlayer].Points)
			TopPlayer = i;
	}
	vector<int> outputList;
	outputList.push_back(TopPlayer);

	//check for draws
	for (int i = 0; i < PlayerCount; i++)
	{
		//check if points match
		if (i != TopPlayer)
			if (Players[i].Points == Players[TopPlayer].Points)
				outputList.push_back(i);
	}

	return outputList;
}
//make turn for 0 based index player
void MakeTurnForHuman(int i)
{
	bool TurnAgain = true;
	while (TurnAgain == true)
	{
		system("cls");
		PrintGame();
		cout << "It is " << Players[i].Name << "'s turn" << endl;

		cout << "Is it safe to start " << Players[i].Name << " turn (and show their cards)?" << endl;
		system("pause");

		//Gather all cards as stirng and print
		cout << "You have these cards: " << GetCardString(i) << endl;

		//Player can now choose to pick cards;
		string CardToSteal;
		bool pickToSteal = true;
		while (pickToSteal == true)
		{
			//Get list of shortend 
			cout << "What card would you like to steal? : ";
			Players[i].UpdateListForSelection();
			for (int k = 0; k < Players[i].QueryListSize - 1; k++)
			{
				cout << Players[i].QueryList[k] << ", ";
			}
			cout << Players[i].QueryList[Players[i].QueryListSize - 1] << endl;

			//select card to steal
			cin >> CardToSteal;
			//check if the player has one of those cards
			bool match = false;
			for (int k = 0; k < Players[i].QueryListSize; k++)
			{
				if (Players[i].QueryList[k] == CardToSteal);
				{
					match = true;
				}
			}
			if (match == true)
			{
				pickToSteal = false;
			}
			else
			{
				cout << "You do not have any " << CardToSteal << endl;
			}
		}

		system("cls");
		PrintGame();

		//Select player to steal from
		int PlayerToStealFrom;
		bool getPlayerToStealFrom = true;
		while (getPlayerToStealFrom == true)
		{
			cout << "Select a player to steal a " << CardToSteal << " from" << endl;
			//print out the other players 1,2,3 and 4
			//excluding current player
			for (int k = 0; k < PlayerCount; k++)
			{
				if (k != i)
					cout << Players[k].Name << " (" << (k + 1) << ") ";
			}
			cout << endl;

			//read user input
			string read;
			cin >> read;
			int readint = atoi(read.c_str());
			//check if valid integer
			if (readint != -1)
			{
				//check if integer is large enough
				if (readint < PlayerCount + 1)
				{
					//if not the current player
					if (readint != i + 1)
					{
						PlayerToStealFrom = readint - 1;
						getPlayerToStealFrom = false;
					}
					else cout << "This is the current player (" << Players[i].Name << ") , please choose another" << endl;
				}
				else cout << "Must be within the player count, please try again" << endl;
			}
			else cout << "Invalid integer, please try again" << endl;
		}

		//AttemptSteal from player
		//This function will have done the steal if it returns true
		bool GoFish = AttemptSteal(i, PlayerToStealFrom, CardToSteal);
		if (GoFish == false)
		{
			//attempt failed, go fish
			PlayerGoFish(i);
			TurnAgain = false;
		}
		cout << "End turn?" << endl;
		system("pause");

		//check if player has no cards
		if (Players[i].PlayerCards.size() == 0)
		{
			if (DeckSize >= 7)
			{
				//draw 7 more cards
				for (int i = 0; i < 7; i++)
				{
					Card cardToAdd = TheDeck[0];
					Players[i].AddCard(cardToAdd);
					TheDeck.erase(TheDeck.begin());
					DeckSize -= 1;
				}
				cout << "You have drawn " << 7 << " cards" << endl;
			}
			else
			{
				//draw remaining cards
				for (int i = 0; i < DeckSize; i++)
				{
					Card cardToAdd = TheDeck[0];
					Players[i].AddCard(cardToAdd);
					TheDeck.erase(TheDeck.begin());
					DeckSize -= 1;
					TurnAgain = false;
				}
				cout << "You have drawn " << DeckSize << " cards" << endl;
			}
		}
	}
}
//make turn for 0 based index player
void MakeTurnForAI(int i)
{
	bool TurnAgain = true;
	while (TurnAgain == true)
	{
		//make sure the turn is truly over
		if (Players[i].PlayerCards.size() == 0)
			if (DeckSize == 0)
			{
				TurnAgain = false;
				break;
			}


		system("cls");
		PrintGame();
		cout << "It is " << Players[i].Name << "'s turn" << endl;

		//Player can now choose to pick cards;
		string CardToSteal;
		//select which one to steal
		Players[i].UpdateListForSelection();
		int whichOne = rand() % Players[i].QueryList.size();
		CardToSteal = Players[i].QueryList[whichOne];

		system("cls");
		PrintGame();

		//Select player to steal from
		int PlayerToStealFrom;
		bool getPlayerToStealFrom = true;
		while (getPlayerToStealFrom == true)
		{
			int PlayerPick = rand() % PlayerCount;
			//excluding current player
			if (PlayerPick != i)
			{
				PlayerToStealFrom = PlayerPick;
				getPlayerToStealFrom = false;
			}
		}

		//AttemptSteal from player
		//This function will have done the steal if it returns true
		bool GoFish = AttemptSteal(i, PlayerToStealFrom, CardToSteal);
		if (GoFish == false)
		{
			//attempt failed, go fish
			PlayerGoFish(i);
			TurnAgain = false;
		}

		//check if player has no cards
		if (Players[i].PlayerCards.size() == 0)
		{
			if (DeckSize >= 7)
			{
				//draw 7 more cards
				for (int i = 0; i < 7; i++)
				{
					Card cardToAdd = TheDeck[0];
					Players[i].AddCard(cardToAdd);
					TheDeck.erase(TheDeck.begin());
					DeckSize -= 1;
				}
				cout << "They have drawn " << 7 << " cards" << endl;
			}
			else
			{
				//draw remaining cards
				for (int i = 0; i < DeckSize; i++)
				{
					Card cardToAdd = TheDeck[0];
					Players[i].AddCard(cardToAdd);
					TheDeck.erase(TheDeck.begin());
					DeckSize -= 1;
					TurnAgain = false;
				}
				cout << "They have drawn " << DeckSize << " cards" << endl;
			}
		}
	}
}
void SaveGame(string name)
{
	//save file
	ofstream savefile;
	savefile.open(name);
	if (savefile.is_open())
	{
		savefile << PlayerCount << "\n";
		savefile << DeckSize << "\n";
		for (int x = 0; x < PlayerCount; x++)
		{
			savefile << Players[x].Name << "\n";
			int ai = 0;
			if (Players[x].AI == 1)
				ai = 1;
			savefile << ai << "\n";
			savefile << Players[x].PlayerCards.size() << "\n";
			for (int y = 0; y < Players[x].PlayerCards.size(); y++)
			{
				savefile << Players[x].PlayerCards[y].Num << "\n";
				savefile << Players[x].PlayerCards[y].Suit << "\n";
			}
		}
		for (int x = 0; x < DeckSize; x++)
		{
			savefile << TheDeck[x].Num << "\n";
			savefile << TheDeck[x].Suit << "\n";
		}
		savefile.close();
	}
	//if an error occured
	else std::cout << "Unable to save game :'(" << std::endl;
}
void LoadGame(string name)
{
	//load game
	ifstream openfile;
	openfile.open(name);
	//if can open
	if (openfile.is_open())
	{
		//get global variables
		string line;
		getline(openfile, line);
		PlayerCount = atoi(line.c_str());
		getline(openfile, line);
		DeckSize = atoi(line.c_str());
		for (int x = 0; x < PlayerCount; x++)
		{
			//player
			getline(openfile, line);
			string name = line;
			getline(openfile, line);
			int ai = atoi(line.c_str());
			bool isAI = false;
			if (ai != 0)
				isAI = true;
			Players.push_back(Player(name, isAI));

			//player cards
			getline(openfile, line);
			int PlayerCardsSize = atoi(line.c_str());
			for (int y = 0; y < PlayerCardsSize; y++)
			{
				//get card
				getline(openfile, line);
				int Num = atoi(line.c_str());
				getline(openfile, line);
				int Suit = atoi(line.c_str());
				Players[x].AddCard(Card(Num, Suit));
			}
		}
		//get deck
		for (int x = 0; x < DeckSize; x++)
		{
			getline(openfile, line);
			int Num = atoi(line.c_str());
			getline(openfile, line);
			int Suit = atoi(line.c_str());
			TheDeck.push_back(Card(Num, Suit));
		}
		openfile.close();
	}
	//the error handling is in the main void
}
int main()
{
	//seed random number
	srand(time(NULL));

	//initialise deck
	for (int value = 1; value < 14; value++)
		for (int suit = 0; suit < 4; suit++)
			TheDeck.push_back(Card(value, suit));
	//shuffle the deck a few times
	ShuffleDeck(1 + rand() % 3);

	//initialise players with i as player number. 1 based index.

	cout << "Welcome! I hope you enjoy this game!" << endl;

	//get save or load
	cout << "Did you want to start a new game (n) or load one (l)" << endl;
	cout << "Please know the autosave is autosaved as: " << DefaultSaveName << endl;
	bool getNorL = true;
	while (getNorL == true)
	{
		string read;
		cin >> read;
		if (read == "n")
		{
			//break loop
			getNorL = false;
			//get new game conditions
			//Get player count
			bool getPlayerCount = true;
			while (getPlayerCount == true)
			{
				cout << "How many players do you wish to play with? (2-4)" << endl;
				string read;
				cin >> read;
				int numP = atoi(read.c_str());
				if (numP != -1)
				{
					if (numP > 1)
					{
						if (numP < 5)
						{
							PlayerCount = numP;
							getPlayerCount = false;
						}
						else cout << "Interger too large, please enter an integer between (2-4)" << endl;
					}
					else cout << "Integer too small, please enter an integer between (2-4)" << endl;
				}
				else cout << "Invalid command, please enter an integer (2-4)" << endl;
			}

			//Get player names and AI capability
			for (int i = 0; i < PlayerCount; i++)
			{
				//name
				string PlayerName;
				bool getPlayerName = true;
				while (getPlayerName == true)
				{
					int playerNumber = i + 1;
					cout << "What is the name of player: " << playerNumber << endl;
					string read;
					cin >> read;
					if (read.size() > 0)
					{
						PlayerName = read;
						getPlayerName = false;
					}
					else cout << "No input given, please give a name" << endl;
				}
				//AI
				bool getIsAI = true;
				while (getIsAI == true)
				{
					cout << "Will this player be AI controlled? (y/n)" << endl;
					string read;
					cin >> read;
					if (read == "y")
					{
						Players.push_back(Player(PlayerName, true));
						getIsAI = false;
					}
					else
					{
						if (read == "n")
						{
							Players.push_back(Player(PlayerName, false));
							getIsAI = false;
						}
						else cout << "I am sorry, I cannot understand this input, please try again" << endl;
					}
				}
			}
			//check if all AI
			for (int i = 0; i < PlayerCount; i++)
			{
				if (Players[i].AI == false)
					allAI = false;
			}
			//SaveName
			bool getSaveName = true;
			while (getSaveName == true)
			{
				std::cout << "Please specifiy a filename to save to:" << std::endl;
				std::cin >> read;
				SaveFileName = read;
				//can remove while loop
				getSaveName = false;
			}

			//Deal cards- 7 times the amount of players
			for (int i = 0; i < 7; i++)
				for (int k = 0; k < PlayerCount; k++)
				{
					//add to player then remove from the 'TheDeck' vector list.
					Card cardToAdd = TheDeck[0];
					Players[k].AddCard(cardToAdd);
					TheDeck.erase(TheDeck.begin());
					DeckSize -= 1;
				}
		}
		else
		{
			if (read == "l")
			{
				//break loop
				getNorL = false;
				//load a game!-all conditions including cards
				bool GoodFile = false;
				while (GoodFile == false)
				{
					cout << "Please specify a file to load:" << endl;
					cin >> read;
					//check if it exists
					ifstream f(read.c_str());
					GoodFile = f.good();
					//bad file
					if (GoodFile == false)
					{
						system("cls");
						std::cout << "File does not exist, please try again" << std::endl;
					}
					else
					{
						SaveFileName = read;
					}
				}
				LoadGame(SaveFileName);
			}
			else cout << "I am sorry, I could not understand that command, please try again" << endl;
		}
	}
	system("cls");

	//start playing until no cards left-bool changed under enclosed braces
	bool makeTurn = true;
	while (makeTurn == true)
	{
		if (allAI == false)
		{
			//give option to make turn or save
			bool getCommand = true;
			while (getCommand == true)
			{
				cout << "Would you like to play another round of hands (p) or save the game (s)?" << endl;
				string read;
				cin >> read;

				//make turn
				if (read == "p")
				{
					getCommand = false;
				}
				else
				{
					if (read == "s")
					{
						getCommand = false;
						SaveGame(SaveFileName);
					}
					else cout << "I am sorry, I didn't get that command could you please try again" << endl;
				}
			}
		}
		//make turn for each player
		for (int i = 0; i < PlayerCount; i++)
		{
			if (Players[i].PlayerCards.size() > 0)
			{
				if (Players[i].AI == true)
					MakeTurnForAI(i);
				else MakeTurnForHuman(i);
			}
			else
			{
				if (DeckSize == 0)
					makeTurn = false;
			}
		}

		//end of playing?
		//no cards left
		bool noCardsLeft = true;
		//Check if players have cards left
		for (int k = 0; k < PlayerCount; k++)
		{
			if (Players[k].PlayerCards.size() != 0)
			{
				//break the loop, we are still playing
				noCardsLeft = false;
				break;
			}
		}
		if (noCardsLeft == true)
		{
			//finish the game
			makeTurn = false;
		}
		//autosave
		SaveGame(DefaultSaveName);
	}
	//Who has the most points?
	vector<int> WinningPlayers = WhoWon();
	int NumofWinners = WinningPlayers.size();
	cout << "Congratulations ";
	for (int i = 0; i < NumofWinners - 1; i++)
		cout << Players[WinningPlayers[i]].Name << ", ";
	cout << Players[WinningPlayers[NumofWinners - 1]].Name << " won!" << endl;

	cout << "Thank you for playing!" << endl;
	system("pause");
	return 0;
}