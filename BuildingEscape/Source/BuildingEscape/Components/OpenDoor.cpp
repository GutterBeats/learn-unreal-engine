// Copyright © Anthony Lesch 2020

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	
	InitialYaw = Owner->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenDoorAngle += InitialYaw;

	if (!IsValid(PressurePlate))
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component, but no PressurePlate set."), *Owner->GetName());
	}

	ActorThatOpened = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(PressurePlate))
	{
		return;
	}
	
	if (PressurePlate->IsOverlappingActor(ActorThatOpened))
	{
		OpenDoor(DeltaTime);

		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		const float TimeSinceOpen = GetWorld()->GetTimeSeconds() - DoorLastOpened;
		if (TimeSinceOpen >= DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(const float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenDoorAngle, DeltaTime, DoorOpenSpeed);
	
	const FRotator OpenDoor(0.f, CurrentYaw, 0.f);
	GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::CloseDoor(const float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);

	const FRotator CloseDoor(0.f, CurrentYaw, 0.f);
	GetOwner()->SetActorRotation(CloseDoor);
}

