#pragma once
#ifndef CARD_H
#define CARD_H

class Card
{
public:
	Card(int value, int suit);
	~Card();
	int Num;
	int Suit;
};

#endif