#include "QPlayerController.h"

#include "EnhancedInputSubsystems.h"

AQPlayerController::AQPlayerController():
InputMappingContext(nullptr),
MoveAction(nullptr),
LookAction(nullptr)
{
	
}

void AQPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1,5,FColor(EPhysicalMaterialMaskColor::Cyan),TEXT("입력됨\n"));
	
	TObjectPtr<ULocalPlayer> LocalPlayer = GetLocalPlayer();
	if (!IsValid(LocalPlayer)) return;
	
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = 
		LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(Subsystem)) return;
	
	if (InputMappingContext)
	{
		Subsystem->AddMappingContext(InputMappingContext,0);
	}
}




