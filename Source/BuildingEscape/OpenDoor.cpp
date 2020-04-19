// Copyright Will Webster 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	m_TargetYaw += m_CurrentYaw = m_InitialYaw = GetOwner()->GetActorRotation().Yaw;
	//m_TargetYaw += 90.f;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_CurrentYaw = FMath::FInterpTo(m_CurrentYaw, m_TargetYaw, DeltaTime, 2);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), m_CurrentYaw);

	FRotator doorRotation = GetOwner()->GetActorRotation();
	doorRotation.Yaw = m_CurrentYaw;
	GetOwner()->SetActorRotation(doorRotation);
}

