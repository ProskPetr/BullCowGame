#pragma once

#include <string>

// to match Unreal Engine standards
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

enum class EGuessStatus
{
	OK,
	WRONG_LENGTH,
	WRONG_CASE,
	NOT_ISOGRAM,
	NOT_A_WORD
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	void PrintIntro() const;
	void MakeGuess();
	void EndGame() const;
	bool PlayAgain();
	

private:
	// see constructor for initialisation
	int32 CurrentTry;
	FString HiddenWord;
	bool bIsogramGuessed;
	
	EGuessStatus ValidateGuess(FString);
	FBullCowCount SubmitGuess(FString);
	int32 GetMaxTries() const;
	bool IsWord(FString);
	bool IsLowercase(FString);
	bool IsIsogram(FString);
	
};
