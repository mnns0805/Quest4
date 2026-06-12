
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemRotate.generated.h"

UCLASS()
class QUESTPROJECT_API AItemRotate : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemRotate();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "ItemRotate|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "ItemRotate|Rotate")
	float RotationSpeed;
};
