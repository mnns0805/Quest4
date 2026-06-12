#include "QCharacter.h"

#include "EnhancedInputComponent.h"
#include "QPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"


AQCharacter::AQCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetSimulatePhysics(false);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	SkeletalMeshComponent->SetSimulatePhysics((false));
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
	
}

void AQCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	TObjectPtr<UEnhancedInputComponent> EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInput)) return;
	
	TObjectPtr<AQPlayerController> PlayerController = Cast<AQPlayerController>(GetController());
	if (!IsValid(PlayerController)) return;
	
	//액션인풋
	if (PlayerController->MoveAction)
	{
		EnhancedInput->BindAction(PlayerController->MoveAction,
		ETriggerEvent::Triggered,this,&AQCharacter::Move);
	}
	
		
	if (PlayerController->LookAction)
	{
		EnhancedInput->BindAction(PlayerController->LookAction,
		ETriggerEvent::Triggered,this,&AQCharacter::Look);
	}
}


void AQCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	const FVector2D MoveInput = Value.Get<FVector2D>();
	FRotator TagetRotation = FRotator(0,GetControlRotation().Yaw,GetControlRotation().Roll);
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector ForwardDirection = TagetRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MoveInput.X);
	}	
	
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector RightDirection = TagetRotation.RotateVector(FVector::RightVector);;
		AddMovementInput(RightDirection, MoveInput.Y);
	}
}

void AQCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}