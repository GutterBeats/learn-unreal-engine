// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

enum EGameOutcome { Win, Lose };

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge final : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	FBullCowCount GetBullCows(const FString& Guess) const;

	private:
	void InitializeGame();
	void PrintWelcomeMessage(const FString&);
	void InitializeValidWordList();
	void ProcessGuess(const FString&);
	void EndGame(const EGameOutcome);

	static bool IsIsogram(const FString&);
	
	bool bGameStart;
	FString HiddenWord;
	int32 Lives;
	TArray<FString> Isograms;
};
