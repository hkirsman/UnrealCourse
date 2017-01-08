//
//  FBullCowGame.hpp
//  BullCowGame logic.
//  The game is a simple guess the word game based on Mastermind.
//
//  Created by Hannes Kirsman on 07/01/17.
//  Copyright © 2017 Hannes Kirsman. All rights reserved.
//

#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// All values initialized to zero.
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    void Reset();
    FBullCowCount SubmitValidGuess(FString);

private:
    // see constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bIsGameWon;
    
    bool IsIsogram(FString) const;
    bool isLowercase(FString) const;
};

#endif /* FBullCowGame_hpp */
