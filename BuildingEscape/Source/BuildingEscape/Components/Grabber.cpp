// Copyright © Anthony Lesch 2020

#include "Grabber.h"

#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandle()
{
	// Checking for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Component is required for use by the Grabber Component. Missing on: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		return;
	}
	
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab()
{
	FHitResult Hit;
	if (!GetFirstPhysicsBodyInReach(OUT Hit)) return;

	PhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, Hit.Location);
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle->GrabbedComponent) return;
	
	// Get players viewpoint
	FVector PlayerLocation;
	FRotator PlayerRotator;
    	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotator);
    
	// Ray-cast out to a certain distance (Reach)
	const FVector LineTraceEnd = PlayerLocation + PlayerRotator.Vector() * Reach;
    
	PhysicsHandle->SetTargetLocation(LineTraceEnd);
}

bool UGrabber::GetFirstPhysicsBodyInReach(FHitResult& HitResult) const
{
	// Get players viewpoint
	FVector PlayerLocation;
	FRotator PlayerRotator;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotator);

	// Ray-cast out to a certain distance (Reach)
	const FVector LineTraceEnd = PlayerLocation + PlayerRotator.Vector() * Reach;
	const FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	return GetWorld()->LineTraceSingleByObjectType(OUT HitResult, PlayerLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
}


