// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    PrintLine(TEXT("Welcome to the BullCow Game!"));
    PrintLine(TEXT("Please type your name and press enter."));
    
    bGameStart = true;
    HiddenWord = TEXT("fail");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (bGameStart)
    {
        PrintWelcomeMessage(Input);
    }
    else
    {
        if (Input.Equals(HiddenWord, ESearchCase::IgnoreCase))
        {
            PrintLine("Congratulations! You're the WINNER.");
        }
        else PrintLine("Oops, you got it wrong.");
    }
}

void UBullCowCartridge::PrintWelcomeMessage(const FString& Name)
{
    if (!bGameStart)
    {
        return;
    }
    
    bGameStart = false;

    const FString WelcomeMessage = TEXT("Welcome " + Name + ", let's play!");
    PrintLine(WelcomeMessage);
}
