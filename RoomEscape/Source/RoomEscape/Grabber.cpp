// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "Grabber.h"

#define OUT
#define PHYSICS_HANDLE_CHECK if (!physicsHandle) { return; }

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
	findPhysicsHandle();
	bindInput();
}

void UGrabber::findPhysicsHandle() {
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle) {
		; //do nothing;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not find PhysicsHandle for %s"), *GetOwner()->GetName());
	}
}

void UGrabber::bindInput() {
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent) {
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not find InputComponent for %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PHYSICS_HANDLE_CHECK

	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);
	FVector end = location + rotation.Vector()*REACH;

	if( physicsHandle->GrabbedComponent) {
		physicsHandle->SetTargetLocation(end);
	}
}

void UGrabber::Grab() {

	PHYSICS_HANDLE_CHECK

	UE_LOG(LogTemp, Warning, TEXT("DO THE THING!"));
	FVector location;
	FRotator rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT location, OUT rotation);
	FVector end = location + rotation.Vector()*REACH;
	DrawDebugLine(GetWorld(), location, end, FColor::Red);

	FHitResult hitResult;
	FCollisionObjectQueryParams objectQueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);
	bool bGotHit = GetWorld()->LineTraceSingleByObjectType(OUT hitResult, location, end, objectQueryParams);
	if (bGotHit) {
		physicsHandle->GrabComponentAtLocationWithRotation(hitResult.GetComponent(), NAME_None, end, hitResult.GetActor()->GetActorRotation());
	}
}

void UGrabber::Release() {

	PHYSICS_HANDLE_CHECK

	UE_LOG(LogTemp, Warning, TEXT("No longer doing the thing..."));
	physicsHandle->ReleaseComponent();
}