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
	actorsThatCanActivatePlate.Add(GetWorld()->GetFirstPlayerController()->GetPawn());
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	for (auto actor : actorsThatCanActivatePlate) {
		if (pressurePlate->IsOverlappingActor(actor)) {
			RotateOwner(DEFAULT_DEGREES);
			doorShouldCloseTimer = timeDelayForDoorToClose;
			bDoorWasOpenned = true;
		}
	}

	if (bDoorWasOpenned && doorShouldCloseTimer <= 0) {
		RotateOwner(0.0f);
		bDoorWasOpenned = false;
	} else if (bDoorWasOpenned) {
		doorShouldCloseTimer -= DeltaTime;
	}
	
}

void UOpenDoor::RotateOwner(float degrees) const {
	UE_LOG(LogTemp, Warning, TEXT("Rotating Door"))
	FRotator rotator;
	rotator.Yaw = degrees;
	//GetOwner()->EditorApplyRotation(rotator, false, false, false);
	GetOwner()->SetActorRotation(rotator, ETeleportType::None);
}

