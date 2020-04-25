// Copyright Will Webster 2020


#include "Grabber.h"

#include "CollisionQueryParams.h"
//#include "Component/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#define OUT  // doesn't actually do anything, just documentation

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
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
	// checking for physics handle component
	m_PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (m_PhysicsHandle)
	{
		// physics handle found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("no UPhysicsHandleComponent found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	// checking for physics handle component
	m_InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (m_InputComponent)
	{
		// physics handle found
		m_InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		m_InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed!"));

	// see what it hits
	AActor* actorHit = RayCast().GetActor();
	if(actorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(actorHit->GetName()));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released!"));
}

FHitResult UGrabber::RayCast() const
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerViewPointLocation, OUT playerViewPointRotation);
	
	FVector lineTraceEnd = playerViewPointLocation + (playerViewPointRotation.Vector() * m_Reach);
	//DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor::Red, false, 0.f, 0.f, 1.f);  // debug

	// Raycast out to a certain distance (m_Reach)
	FHitResult hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(hit, playerViewPointLocation, lineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	
	return hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

