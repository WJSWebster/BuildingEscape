// Copyright Will Webster 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;
class UInputComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Grab();
	void Release();
	FHitResult RayCast() const;  // return the first actor within reach with physics body

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void FindPhysicsHandle();
	void SetupInputComponent();

	UPROPERTY(EditAnywhere)
		float m_Reach = 100.f;
	UPhysicsHandleComponent* m_PhysicsHandle = nullptr;
	UInputComponent* m_InputComponent = nullptr;
};
