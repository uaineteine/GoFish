#include "stdafx.h"
#include "Player.h"

//constructor to pass name down
Player::Player(string name, bool isComputerControlled)
{
	Name = name;
	AI = isComputerControlled;
	Points = 0;
	QueryListSize = 0;
}

Player::~Player()
{
}


string Name;
vector<Card> PlayerCards;
//dynamic list of just the values of card the player has
//This is for querys on asking for cards from the others
vector<string> QueryList;
//This keeps track of how many duplicate rank the player has
//needed for checking if there is 4 of one rank.
vector<int> QueryListDuplicateCount;
int Points = 0; //default of 0
int QueryListSize = 0; //default of 0
bool isComputerControlled;

void Player::UpdateList(Card newCard)
{
	//check if new card already exists in querylist
	bool match = false;
	string Value = to_string(newCard.Num);
	for (int j = 0; j < QueryListSize; j++)
	{
		if (Value == QueryList[j])
		{
			QueryListDuplicateCount[j] += 1;
			match = true;
			break;
		}
	}
	//if there is no match, the list needs to be updated
	if (match == false)
	{
		QueryList.push_back(Value);
		QueryListDuplicateCount.push_back(1);
		QueryListSize += 1;
	}
}
void Player::UpdateListForSelection()
{
	QueryList.clear();
	QueryListDuplicateCount.clear();
	QueryListSize = 0;
	for (int i = 0; i < PlayerCards.size(); i++)
	{
		UpdateList(PlayerCards[i]);
	}
}
void Player::AddCard(Card newCard)
{
	//add
	PlayerCards.push_back(newCard);
	//update querylist
	UpdateList(newCard);
	//check if player gains points
	CheckForPoints();
}
void Player::RemoveCardByIndex(int removeThisCard)
{
	//erase
	PlayerCards.erase(PlayerCards.begin() + removeThisCard);
	UpdateListForSelection();
}

void Player::CheckForPoints()
{
	//see if we have duplicates
	int count = 0;
	string Value;
	for (int i = 0; i < PlayerCards.size(); i++)
	{
		int intermediateCount = 0;
		for (int k = 0; k < PlayerCards.size(); k++)
		{
			if (PlayerCards[i].Num == PlayerCards[k].Num)
			{
				intermediateCount += 1;
			}
			if (intermediateCount == 4)
			{
				count = 4;
				Value = to_string(PlayerCards[i].Num);
				break;
			}
		}
	}

	if (count == 4)
	{
		//remove
		for (int k = 0; k < 4; k++)
		{
			for (int i = 0; i < PlayerCards.size(); i++)
			{
				if (to_string(PlayerCards[i].Num) == Value)
				{
					PlayerCards.erase(PlayerCards.begin() + i);
				}
			}
		}

		//get query pos
		int pos;
		for (int i = 0; i < QueryListSize; i++)
		{
			if (QueryList[i] == Value)
				pos = i;
		}
		QueryList.erase(QueryList.begin() + pos);
		QueryListDuplicateCount.erase(QueryListDuplicateCount.begin() + pos);
		QueryListSize -= 1;

		//we have 4 of the cards, add point
		Points += 1;
		cout << "Yay, " << Name << " has got a set of 4 " << Value << "s They are now on " << Points << " points!" << endl;
		system("pause");
	}
}


//obsolete
/*void Player::CheckForPoints()
{
	string FourCardsOf;
	int FourCardsMatchPos;
	bool GotPoint = false; //by default
	//check for 4 matches through all cards (vector search)
	for (int i = 0; i < QueryListSize; i++)
	{
		if (QueryListDuplicateCount[i] == 4)
		{
			FourCardsOf = QueryList[i];
			FourCardsMatchPos = i;
			GotPoint = true;
		}
	}
	//if got a point, remove all 4 cards
	if (GotPoint == true)
	{
		//my programming is not perfect, ensure no mistakes here before removing
		bool overide = false;
		int count = 0;
		for (int i = 0; i < PlayerCards.size(); i++)
			if (to_string(PlayerCards[i].Num) == FourCardsOf)
				count += 1;
		if (count != 4)
			overide = true;
		if (overide == false)
		{
			for (int i = 0; i < PlayerCards.size(); i++)
			{
				if (to_string(PlayerCards[i].Num) == FourCardsOf)
				{
					PlayerCards.erase(PlayerCards.begin() + i);
				}
			}
			QueryList.erase(QueryList.begin() + FourCardsMatchPos);
			QueryListDuplicateCount.erase(QueryListDuplicateCount.begin() + FourCardsMatchPos);
			QueryListSize -= 1;

			//we have 4 of the cards, add point
			Points += 1;
			cout << "Yay, " << Name << " has got a set of 4 " << FourCardsOf << "s They are now on " << Points << " points!" << endl;
			system("pause");
		}
	}
}*/