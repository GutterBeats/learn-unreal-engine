// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <cstdlib>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("Resources/WordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
    srand(time(0));
    
    InitializeGame();
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (bGameStart)
    {
        PrintWelcomeMessage(Input);
        return;
    }
    
    if (Input.Equals(HiddenWord, ESearchCase::IgnoreCase))
    {
        PrintLine(TEXT("Congratulations! You're the WINNER."));
        return;
    }
    
    const int32 CharacterDifference = HiddenWord.Len() - Input.Len();

    if (CharacterDifference > 0)
    {
        PrintLine(TEXT("Almost! You were %i character(s) under."), CharacterDifference);
    }
    else if (CharacterDifference < 0)
    {
        PrintLine(TEXT("So close. You were %i character(s) over."), CharacterDifference * -1);
    }
            
    --Lives;
}

void UBullCowCartridge::InitializeGame()
{
    PrintLine(TEXT("Welcome to the BullCow Game!"));
    PrintLine(TEXT("Please type your name and press enter."));

    const int Random = rand() % WordList.Num();
    PrintLine(TEXT("The random number is: %i"), Random);
    
    bGameStart = true;
    HiddenWord = WordList[Random];
    Lives = 4;
}

void UBullCowCartridge::PrintWelcomeMessage(const FString& Name)
{
    if (!bGameStart)
    {
        return;
    }
    
    bGameStart = false;

    PrintLine(TEXT("Welcome %s, let's play!"), *Name);
    PrintLine(TEXT("There are %i possible words."), WordList.Num());
}
