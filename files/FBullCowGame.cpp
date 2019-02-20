#pragma once

#include "FBullCowGame.h"
#include <iostream>
#include <map>
#define TMap std::map // to match Unreal Engine standards


FBullCowGame::FBullCowGame()
{
	const FString HIDDEN_WORD = "planet"; // MUST be isogram
	HiddenWord = HIDDEN_WORD;

	CurrentTry = 1;
	bIsogramGuessed = false;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[HiddenWord.length()];
}

void FBullCowGame::PrintIntro() const
{
	std::cout << R"(
         .-=-.                .-=-.            .=     ,        =.
           `) )              ( (`      _  _   /'/    )\,/,/(_   \ \
          .' /                \ '.      `//-.|  (  ,\\)\//\)\/_  ) |
         (  (   _.-'`::`'-._   )  )     //___\   `\\\/\\/\/\\///'  /
          \  `'`    .::.    `'`  /   ,-"~`-._ `"--'_   `"""`  _ \`'"~-,_
           `-._\`~`      `~`/_.-'    \       `-.  '_`.      .'_` \ ,-"~`/
          _,=` /            \ `=,_    `.__.-'`/   (-\        /-) |-.__,'
         (    ,(^\        /^),    )     ||   |     \O)  /^\ (O/  |
          `~~` \0)\      /(0/ `~~`      `\\  |         /   `\    /
                | /`    '\ |              \\  \       /      `\ /
                |          |               `\\ `-.  /' .---.--.\
                |          |                 `\\/`~(, '()      ('
                |          |                  /(O) \\   _,.-.,_)
                /          \                 //  \\ `\'`      /
                \()      ()/               / |  ||   `""""~"`
                 `._-==-_.'               /'  |__||
                    `""`                        `o
                    BULL           AND                 COW
                            A funny word game)";
	std::cout << "\n\n\n";
	std::cout << "Can you guess the " << HiddenWord.length();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void FBullCowGame::MakeGuess()
{
	while (CurrentTry <= GetMaxTries() && !bIsogramGuessed)
	{		
		std::cout << "Try " << CurrentTry << "/" << GetMaxTries() << ". Make a guess: ";
		FString Guess = "";
		std::getline(std::cin, Guess);

		EGuessStatus Status = ValidateGuess(Guess);
		switch (Status)
		{
		case EGuessStatus::NOT_A_WORD:
			std::cout << "Please enter a word" << "\n\n";
			continue;
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << HiddenWord.length() << " letter word." << "\n\n";
			continue;
		case EGuessStatus::WRONG_CASE:
			std::cout << "All letters should be in lowercase" << "\n\n";
			continue;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter isogram (all letters should be different)" << "\n\n";
			continue;
		default:
			break;
		}

		FBullCowCount Count = SubmitGuess(Guess);

		std::cout << "Bulls: " << Count.Bulls << "\n";
		std::cout << "Cows: " << Count.Cows << "\n\n";
	}

	return;
}

EGuessStatus FBullCowGame::ValidateGuess(FString Guess)
{
	if (!IsWord(Guess))
	{
		return EGuessStatus::NOT_A_WORD;
	}
	else if (Guess.length() != HiddenWord.length())
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::WRONG_CASE;
	}
	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsWord(FString Word)
{
	for (auto Letter : Word)
	{
		if (!isalpha(Letter))
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word)
{
	for (auto Letter : Word)
	{
		if (Letter != tolower(Letter)) {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsIsogram(FString Word)
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	
	return true;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;
	int32 IsogramLength = HiddenWord.length();
	int32 GuessLength = Guess.length();

	for (int32 i = 0; i < GuessLength; i++)
	{
		for (int32 j = 0; j < IsogramLength; j++)
		{
			if (j == i && HiddenWord[j] == Guess[i])
			{
				BullCowCount.Bulls++;
			}
			else if (j != i && HiddenWord[j] == Guess[i])
			{
				BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWord.length())
	{
		bIsogramGuessed = true;
	}

	return BullCowCount;
}

void FBullCowGame::EndGame() const
{
	if (bIsogramGuessed)
	{
		std::cout << "You won!" << "\n\n";
	}
	else
	{
		std::cout << "You didn't guesse the word. Try again" << "\n\n";
	}
	return;
}

bool FBullCowGame::PlayAgain()
{
	std::cout << "Do you want to play again?(y/n) ";
	FString Response = "";
	std::getline(std::cin, Response);
	std::cout << "\n";
	return (Response[0] == 'y' || Response[0] == 'Y');
}
