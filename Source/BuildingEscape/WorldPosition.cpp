// Copyright Will Webster 2020


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	/*FString log = TEXT("Hello");
	FString* ptrLog = &log;
	log.Len();
	UE_LOG(LogTemp, Warning, TEXT("%s!"), **ptrLog)*/

	FString objectName;
	objectName = GetOwner()->GetName();

	FString objectPosition = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s's position in world is: %s"), *objectName, *objectPosition)
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

