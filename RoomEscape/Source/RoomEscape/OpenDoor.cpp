// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	float totalMass = GetTotalMassOnPlate();
	
	if (totalMass >= massNeeded) {
		doorShouldCloseTimer = timeDelayForDoorToClose;
		if (!bIsDoorOpen) {
			RotateOwner(DEFAULT_DEGREES);
			bIsDoorOpen = true;
		}
	}
	

	if (bIsDoorOpen && doorShouldCloseTimer <= 0) {
		RotateOwner(-DEFAULT_DEGREES);
		bIsDoorOpen = false;
	} else if (bIsDoorOpen) {
		doorShouldCloseTimer -= DeltaTime;
	}
	
}

float UOpenDoor::GetTotalMassOnPlate() const {
	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;
	pressurePlate->GetOverlappingActors(overlappingActors);
	for (auto actor : overlappingActors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Total Mass on plate: %f"), totalMass)
	return totalMass;
}

void UOpenDoor::RotateOwner(float degrees) const {
	UE_LOG(LogTemp, Warning, TEXT("Rotating Door"))
	FRotator rotator;
	rotator.Yaw = degrees;
	GetOwner()->EditorApplyRotation(rotator, false, false, false);
	//GetOwner()->SetActorRotation(rotator, ETeleportType::None);
}



