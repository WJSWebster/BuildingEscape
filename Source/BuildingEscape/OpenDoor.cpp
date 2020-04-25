// Copyright Will Webster 2020

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"

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

	m_TargetYaw += m_CurrentYaw = m_InitialYaw = GetOwner()->GetActorRotation().Yaw;

	//check(m_PressurePlate != nullptr);
	if (m_PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no PressurePlate set!"), *GetOwner()->GetName())
	}

	m_OpeningActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_PressurePlate->IsOverlappingActor(m_OpeningActor) && m_CurrentYaw != m_TargetYaw)
	{
		OpenDoor(DeltaTime);

		m_DoorLastOpened = GetWorld()->TimeSeconds;
	}
	else if (GetWorld()->TimeSince(m_DoorLastOpened) > m_DoorCloseDelay && m_CurrentYaw != m_InitialYaw)  // if player no longer on pressure plate
	{
		CloseDoor(DeltaTime);
	}

}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	m_CurrentYaw = FMath::FInterpTo(m_CurrentYaw, m_TargetYaw, DeltaTime, m_OpeningSpeed);
	MoveDoor();
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	m_CurrentYaw = FMath::FInterpTo(m_CurrentYaw, m_InitialYaw, DeltaTime, m_ClosingSpeed);
	MoveDoor();
}

void UOpenDoor::MoveDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), m_CurrentYaw);

	FRotator doorRotation = GetOwner()->GetActorRotation();
	doorRotation.Yaw = m_CurrentYaw;
	GetOwner()->SetActorRotation(doorRotation);
}
