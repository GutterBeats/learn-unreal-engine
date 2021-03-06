// Copyright © Anthony Lesch 2020

#pragma once

#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor final : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OpenDoor(const float DeltaTime);
	void CloseDoor(const float DeltaTime);
	
	// The current Yaw
	float CurrentYaw;
	
	// The doors initial Yaw
	float InitialYaw;

	// Time (in seconds) when the door was last opened 
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	// Target rotation for opening / closing door
	float OpenDoorAngle= 90.f;

	UPROPERTY(EditAnywhere)
	// Time (in seconds) to delay before closing door
	float DoorCloseDelay = .5f;

	UPROPERTY(EditAnywhere)
	// Speed at which the door opens
	float DoorOpenSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	// Speed at which the door closes
	float DoorCloseSpeed = 4.f;

	UPROPERTY(EditAnywhere)
	// The associated trigger volume for triggering a door to open
	ATriggerVolume* PressurePlate;

	UPROPERTY(SkipSerialization)
	AActor* ActorThatOpened;
};
