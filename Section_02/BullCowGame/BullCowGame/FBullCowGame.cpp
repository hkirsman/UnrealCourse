//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Hannes Kirsman on 07/01/17.
//  Copyright © 2017 Hannes Kirsman. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 5}, {5, 10}, {6, 15}, {7, 20} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

// Go to beginning of the game.
void FBullCowGame::Reset() {
    const FString HIDDEN_WORD = "bat"; // this MUST be isogram
    
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bIsGameWon = false;
    return;
}

// Check if the guess is valid.
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    if (!IsIsogram(Guess)) { // If the word is not isogram,
        return EGuessStatus::Not_Isogram;
    }
    else if (!isLowercase(Guess)) { // If the guess is not lowercarse
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}

// Send the guess to game.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    // increment the turn number
    MyCurrentTry++;

    // setup return variable
    FBullCowCount BullCowCount;
    
    // loop through all letters in hidden word
    int32 HiddenWordLength = GetHiddenWordLength();
    for (int32 i = 0; i < HiddenWordLength; i++) {
        // compare the letters in against the guess
        for (int32 j = 0; j < HiddenWordLength; j++) {
            if (Guess[i] == MyHiddenWord[j]) {
                if (i == j) {
                    BullCowCount.Bulls++;
                }
                else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == HiddenWordLength && BullCowCount.Cows == 0) {
        bIsGameWon = true;
    }
    else {
         bIsGameWon = false;
    }
    
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    
    for (auto Letter : Word) {
        Letter = tolower(Letter); // handle mixed case
        if (LetterSeen[Letter]) {
            return false;
        }
        else {
            LetterSeen[Letter] = true;
        }
    }
    
    return true;
}

bool FBullCowGame::isLowercase(FString Word) const {
    for (auto Letter : Word) {
        if (Letter != tolower(Letter)) {
            return false;
        }
    }
    
    return true;
}
