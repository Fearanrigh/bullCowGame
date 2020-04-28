// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    // Setting up the game
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver) {
        ClearScreen();
        SetupGame();
    }
    else { // Checking player guess.
        ProcessGuess(Input);
    }
    
    // Check if isogram
    // Prompt to guess again
    // Check if right number of characters
    // Prompt to guess again
    
    // Remove life
    
    // Check if lives > 0
    // If yes, guess again
    // Show lives left
    // If no, show gameover and HiddenWord
    // Prompt to play again, press enter to play again?
    // Check user input
    // Play again or quit?
}

void UBullCowCartridge::SetupGame() {
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Welcome the player
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Enter your guess, and press enter..."));
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
    if(Guess == HiddenWord) {
        PrintLine(TEXT("You Win!"));
        EndGame();
        return;
    }

    Lives--;
    PrintLine(TEXT("You've lost a life!"));
    if(Lives > 0) {
        if(Guess.Len() != HiddenWord.Len()) {
            PrintLine(TEXT("Try another guess, you have %i lives left."), Lives);
        }
    }
    else {
        PrintLine(TEXT("You have no lives left!"));
        EndGame();
    }
}
