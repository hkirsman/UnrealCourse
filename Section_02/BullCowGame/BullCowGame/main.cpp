//
//  main.cpp
//  BullCowGame
//
//  Created by Hannes Kirsman on 06/01/17.
//  Copyright © 2017 Hannes Kirsman. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes outside of class
void PrintIntro();
FText GetGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

// instantiate a new game
FBullCowGame BCGame;

// entry point, main function.
int main(int32 argc, const char * argv[]) {
    PrintIntro();
    do {
        PlayGame();
    }
    while (AskToPlayAgain());
    return 0;
}

void PrintIntro() {
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

FText GetValidGuess() {
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    
    do {
        std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". ";
        std::cout << "Enter you guess: ";
        Guess = "";
        getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please write all leters in lowercase.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "The word is not an isogram.\n\n";
                break;
            default:
                // assume the guess is valid.
                break;
        }
    } while (Status != EGuessStatus::OK); // Keep looping while we don't have any errors.
    
    return Guess;
}

// plays a single game
void PlayGame() {
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    // lool asking for guesses while game is not won
    // and there are still tries remaining.
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();
        
        // Submit valid guess to the game.
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
        std::cout << std::endl;
    }
    
    PrintGameSummary();
    
    return;
}


bool AskToPlayAgain() {
    std::cout << "Do you want to play again with the same hiddenw word? (y/n)";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "Nice work, you won!\n";
    }
    else {
        std::cout << "Sorry, you lost.\n";
    }
    
    return;
}
