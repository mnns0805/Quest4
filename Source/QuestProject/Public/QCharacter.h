#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "QCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;

UCLASS()
class QUESTPROJECT_API AQCharacter : public APawn
{
	GENERATED_BODY()

public:
	AQCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, Category = "QCharacter|Component")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "QCharacter|Component")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "QCharacter|Component")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "QCharacter|Component")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	

};
