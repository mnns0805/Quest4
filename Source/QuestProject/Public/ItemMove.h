#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemMove.generated.h"

UCLASS()
class QUESTPROJECT_API AItemMove : public AActor
{
	GENERATED_BODY()

public:
	AItemMove();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	TObjectPtr<USceneComponent> SceneRootComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "ItemMove|Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "ItemMove|Move")
	float MoveSpeed;
	
	UPROPERTY(VisibleAnywhere,Category = "ItemMove|Move")
	FVector StartLocation;
	FVector MoveLocation;
	
	UPROPERTY(EditAnywhere, Category = "ItemMove|Move")
	FVector MoveAxis;
	
	UPROPERTY(EditAnywhere, Category = "ItemMove|Move")
	float MaxRange;
};
