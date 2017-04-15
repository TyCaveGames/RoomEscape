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
	if (!pressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate unassigned!"))
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	float totalMass = GetTotalMassOnPlate();
	
	if (totalMass >= massNeeded) {
		openEvent.Broadcast();
	} else {
		closeEvent.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnPlate() const {
	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;
	
	if (!pressurePlate) { return totalMass; }

	pressurePlate->GetOverlappingActors(overlappingActors);
	for (auto actor : overlappingActors) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Total Mass on plate: %f"), totalMass)
	return totalMass;
}