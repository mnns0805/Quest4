#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class QUESTPROJECT_API AQPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AQPlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	
	
protected:
	virtual void BeginPlay() override;
};
