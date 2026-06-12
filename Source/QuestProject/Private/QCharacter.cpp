#include "QCharacter.h"

#include "EnhancedInputComponent.h"
#include "MaterialHLSLTree.h"
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
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(CapsuleComponent);
	StaticMeshComponent->SetSimulatePhysics((false));
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->bUsePawnControlRotation = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
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

void AQCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	const FVector2D MoveInput = Value.Get<FVector2D>();
	
	float Delta = GetWorld()->GetDeltaSeconds();
	
	FVector ForwardDirection = FVector::ForwardVector * MoveInput.X * Delta * MoveSpeed;
	FVector RightDirection = FVector::RightVector * MoveInput.Y * Delta * MoveSpeed;
	FVector FinalMove = ForwardDirection + RightDirection;
	
	AddActorLocalOffset(FinalMove);
}

void AQCharacter::Look(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;
	const FVector2D LookInput = Value.Get<FVector2D>();
	
	float FinalYaw = LookInput.X * MouseSensitivity;
	float FinalPitch = LookInput.Y * MouseSensitivity;
	
	AddActorLocalRotation(FRotator(0.0f,FinalYaw,0.0f));	
	SpringArmComponent->AddLocalRotation(FRotator(FinalPitch,0.0f,0.0f));
}