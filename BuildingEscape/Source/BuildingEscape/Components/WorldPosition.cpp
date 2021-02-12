// Copyright © Anthony Lesch 2020

#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// FString Log = "Hello!";
	// FString* PrtLog = &Log;
	//
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *Log);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PrtLog);

	const AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}
	
	const FString ObjectName = Owner->GetName();
	UE_LOG(LogTemp, Warning, TEXT("This component belongs to %s"), *ObjectName);

	const FString ObjectPositionString = Owner->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("The %s is at the position %s."), *ObjectName, *ObjectPositionString);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

