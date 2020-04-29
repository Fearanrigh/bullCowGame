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

bool UBullCowCartridge::IsIsogram(FString Word) const {
    for(int32 i = 0; i < Word.Len(); i++) {
        for(int32 j = i+1; j < Word.Len(); j++) {
            if(Word[i] == Word[j]) {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Would you like to play again?"));
    
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
    if(Guess == HiddenWord) {
        PrintLine(TEXT("You Win!"));
        EndGame();
        return;
    }
    
    // Prompt to guess again
    // Check if right number of characters
    if(Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("The word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Try another guess, you have %i lives left."), Lives);
        return;
    }
    
    // Check if isogram
    if(!IsIsogram(Guess)) {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    // Remove life
    PrintLine(TEXT("You've lost a life!"));
    --Lives;
    
    // Check if lives > 0
    if(Lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        EndGame();
        return;
    }

    // Show player the bulls and the cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}
