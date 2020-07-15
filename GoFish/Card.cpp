#include "stdafx.h"
#include "Card.h"


Card::Card(int value, int suit)
{
	Num = value;
	Suit = suit;
}


Card::~Card()
{
}

int Num;
int Suit;