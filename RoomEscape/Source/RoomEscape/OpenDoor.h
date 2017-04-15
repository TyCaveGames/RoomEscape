// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UOpenDoor : public UActorComponent
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
	const float DEFAULT_DEGREES = 90.f;
	bool bIsDoorOpen = false;
	float doorShouldCloseTimer = -1.f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
	float timeDelayForDoorToClose = 0.1f;
	UPROPERTY(EditAnywhere)
	float massNeeded = 1.0f;

	void RotateOwner(float degrees) const;
	float GetTotalMassOnPlate() const;
};