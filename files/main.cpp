#pragma once

#include "FBullCowGame.h"

FBullCowGame BCGame;

// the entry point of the application
int main()
{
	do
	{
		FBullCowGame BCGame;
		BCGame.PrintIntro();
		BCGame.MakeGuess();
		BCGame.EndGame();
	}
	while (BCGame.PlayAgain());
	
	return 0; // exit application
}
