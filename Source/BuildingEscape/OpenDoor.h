// Copyright Will Webster 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

class ATriggerVolume;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void MoveDoor();

	float m_InitialYaw;
	float m_CurrentYaw;  // doesn't really need to be member var, assigned and used in TickComponent()
	UPROPERTY(EditAnywhere)
		float m_TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* m_PressurePlate;
	UPROPERTY(EditAnywhere)
		AActor* m_OpeningActor;

	UPROPERTY(EditAnywhere)
		float m_OpeningSpeed = 2.f;
	UPROPERTY(EditAnywhere)
		float m_ClosingSpeed = 5.f;
	float m_DoorLastOpened = 0.f;
	UPROPERTY(EditAnywhere)
		float m_DoorCloseDelay = 2.f;
};
