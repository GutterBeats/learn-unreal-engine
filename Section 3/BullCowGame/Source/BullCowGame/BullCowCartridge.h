// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

enum GameOutcome { Win, Lose };

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge final : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	private:
	void InitializeGame();
	void PrintWelcomeMessage(const FString&);
	void GetValidWordList();
	bool IsIsogram(const FString&) const;
	void ProcessGuess(const FString&);
	void EndGame(GameOutcome);
	
	bool bGameStart;
	FString HiddenWord;
	int32 Lives;
	TArray<FString> WordList;
};
