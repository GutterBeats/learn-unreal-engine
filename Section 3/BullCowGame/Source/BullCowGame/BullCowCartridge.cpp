// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <cstdlib>

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    PrintLine(TEXT("Welcome to the BullCow Game!"));
    PrintLine(TEXT("Please type your name and press enter."));

    srand(time(0));
    
    GetValidWordList();
    InitializeGame();

    PrintLine(TEXT("The Hidden word is: %s"), *HiddenWord);
}

void UBullCowCartridge::OnInput(const FString& Input)
{
    ClearScreen();

    if (bGameStart)
    {
        PrintWelcomeMessage(Input);
        return;
    }
    
    if (Input.Equals(HiddenWord, ESearchCase::IgnoreCase))
    {
        EndGame(GameOutcome::Win);
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
    bGameStart = true;
    HiddenWord = WordList[rand() % WordList.Num()];
    Lives = 5;
}

void UBullCowCartridge::PrintWelcomeMessage(const FString& Name)
{
    if (!bGameStart)
    {
        return;
    }
    
    bGameStart = false;

    PrintLine(TEXT("Welcome %s, let's play!"), *Name);
    PrintLine(TEXT("You're trying to guess the %i letter word."), HiddenWord.Len());
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 WordLength = Word.Len();
    for (int32 Index = 0; Index < WordLength; Index++)
    {
        char Character = Word[Index];
        for (int32 NextIndex = Index + 1; NextIndex < WordLength; NextIndex++)
        {
            if (Character == Word[NextIndex])
            {
                return false;
            }
        }
    }

    return true;
}

void UBullCowCartridge::GetValidWordList()
{
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("Resources/WordList.txt");
    TArray<FString> AllWords;

    FFileHelper::LoadFileToStringArray(AllWords, *WordListPath);

    for (FString Word : AllWords)
    {
        if (IsIsogram(Word))
        {
            WordList.Emplace(Word);
        }
    }
}

void UBullCowCartridge::EndGame(GameOutcome Outcome)
{
    switch (Outcome)
    {
    case GameOutcome::Win:
        PrintLine(TEXT("Congratulations! You're a WINNER."));
        break;
    case GameOutcome::Lose:
        PrintLine(TEXT("Ooh, sucks to be you. You're a LOSER."));
        break;
    }

    InitializeGame();
}
