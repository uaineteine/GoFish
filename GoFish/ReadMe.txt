========================================================================
    CONSOLE APPLICATION : GoFish Project Overview
========================================================================

AppWizard has created this GoFish application for you.

This file contains a summary of what you will find in each of the files that
make up your GoFish application.


GoFish.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

GoFish.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

GoFish.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named GoFish.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

----------Go Fish!!!----------


***Assignment details below after how to play***


-----Documentation-----

1. How to play GoFish

  The game is played with 2-4 players with a deck of 52 cards. The object is
  to obtain 4 cards of the same rank for each player,and thus a player
  discards those cards and agains a point. The cards are first dealt out
  with 7 to each player and then, the game begins. Any combination of 4
  may be immeditately discarded and the player gains those points.

  Starting with the first player, a rank is chosen from their hand to
  attempt to steal from another player. If the other player does not have
  a card of this rank, the player must "go fish" and draw from the deck.
  If they are succesful though, they take the card and get another turn.

  If the player runs out of cards and there are still remaining cards, they
  will draw 7 more or take the reaming amount of cards from the deck (if less
  than 7). Once the deck is empty and all sets of 4 are made, the game ends.

  The player with the highest points wins (or draws if there are players with
  the same score).

----------Assignment details and explanation of program----------

  a. Card class

	The game uses a simple card class of two integer variables, a rank and 
	suit. This card class is stored as a dynamic list 'vector' in main class
	to be used as a deck, dealt out with each type of 52 cards. It is also
	kept as a vetor list for each players hand.

	The deck is shuffled using vector shuffle a few times over when
	initialised.

  b. Player class

  	The game keeps the 2-4 players as a vector list of a player class. This 
	class contains variables of a vector list of cards, the player name, points
	and voids to add and remove cards from their hand. It also boasts a query
	list of integers that is updated which keeps the duplicate information of
	cards of the same rank. This is used for asking a player what card they 
	would like to steal.

	The player also features in its constructor the ability to be an AI player.

  d.  AI

	Each new player made will be asked to be a computer controlled player or not.
	The AI makes a random choice of the card to pick from a player, and who to
	pick from.

	This feature was very helpful in debugging!!! The entire game can be AI run,
	as well, so it can be viewed and tested to see if it works without human 
	interaction.

  e. Save and load ability

	The game can be saved, where every new game has a prompt for the save
	filename into the same directory of the program. The game also autosaves to
	an 'autosave.txt' within the same directory per hand (all players take a turn)
	The game can be loaded by filename at the launch of the program 
	The data saved is the Playercount, DeckSize, Players (AI, Name, Cards) and the
	deck cards
	(See voids 'SaveGame' and 'LoadGame')

/////////////////////////////////////////////////////////////////////////////
