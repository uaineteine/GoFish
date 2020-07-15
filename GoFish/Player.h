#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Player
{
public:
	Player(string name, bool isComputerControlled);
	~Player();
	string Name;
	vector<Card> PlayerCards;
	vector<string> QueryList;
	int QueryListSize;
	int Points;
	bool AI;
	void AddCard(Card newCard);
	void RemoveCardByIndex(int removeThisCard);
	void UpdateListForSelection();
private:
	void UpdateList(Card newCard);
	void CheckForPoints();
};

#endif