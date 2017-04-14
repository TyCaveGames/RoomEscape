// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle) {
		; //do nothing;
	} else {
		UE_LOG(LogTemp, Error, TEXT("Could not find PhysicsHandle for %s"), *GetOwner()->GetName());
	}

	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent) {
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		UE_LOG(LogTemp, Error, TEXT("Could not find InputComponent for %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector location;
	FRotator rotation;
	// ...
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);
	FVector end = location + rotation.Vector()*REACH;
	DrawDebugLine(GetWorld(), location, end, FColor::Red);

	FHitResult hitResult;
	FCollisionObjectQueryParams objectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	bool bGotHit = GetWorld()->LineTraceSingleByObjectType(OUT hitResult, location, end, objectQueryParams);
	if (bGotHit) {
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *hitResult.GetActor()->GetName())
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("DO THE THING!"));
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("No longer doing the thing..."));
}