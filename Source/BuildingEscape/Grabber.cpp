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

// checking for physics handle component
void UGrabber::FindPhysicsHandle()
{
	m_PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!m_PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("no UPhysicsHandleComponent found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	m_InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (m_InputComponent)
	{
		m_InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		m_InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	// see what it hits
	FHitResult hitResult = GetFirstPhysicsBodyInReach();
	//UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
	AActor* actorHit = hitResult.GetActor();

	if(actorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(actorHit->GetName()));

		if (!m_PhysicsHandle) { return; }
		m_PhysicsHandle->GrabComponentAtLocation(hitResult.GetComponent(), NAME_None, GetPlayerViewPointReach());
	}
}

void UGrabber::Release()
{
	if (!m_PhysicsHandle) { return; }

	m_PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetPlayerViewPointReach() const
{
	FVector position;
	return GetPlayerViewPointPosAndReach(position);
}

FVector UGrabber::GetPlayerViewPointPosAndReach(FVector& Position) const
{
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT Position, OUT playerViewPointRotation);

	return Position + (playerViewPointRotation.Vector() * m_Reach);  // i.e. the end
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector playerViewPointLocation, lineTraceEnd = GetPlayerViewPointPosAndReach(playerViewPointLocation);
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

	if (m_PhysicsHandle->GrabbedComponent)
	{
		m_PhysicsHandle->SetTargetLocation(GetPlayerViewPointReach());
	}
}

