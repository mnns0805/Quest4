#include "QuestProject/Public/ItemMove.h"

#include "ScreenPass.h"

AItemMove::AItemMove()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("SceneRootComponent");
	SetRootComponent(SceneRootComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(SceneRootComponent);
	
	MoveSpeed = 100.0f;
	MoveAxis = FVector(0.0f,0.0f,0.0f);
	MaxRange = 0.0f;
}

void AItemMove::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation(); //원점
}

void AItemMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//방어코드
	if (!FMath::IsNearlyZero(MoveSpeed))
	{
		FVector NormalizeAxis = MoveAxis.GetSafeNormal(); //축방향 어떤 값이 와도 무조건 1로 고정
		MoveLocation = GetActorLocation()+NormalizeAxis*(MoveSpeed*DeltaTime);
		SetActorLocation(MoveLocation);
		const float MovingLength = FVector::Dist(StartLocation,MoveLocation); 
		
		//왕복운동을 위한 방향역전 로직
		if (MaxRange <= MovingLength)
		{
			MoveAxis *= -1.0f; //축방향반전
			MoveLocation = StartLocation+MaxRange*NormalizeAxis; //움직임방향역전공식
			SetActorLocation(MoveLocation); //오차방지를 위한 좌표세팅
			GEngine->AddOnScreenDebugMessage(-1,60.f,FColor::Red,*GetActorLocation().ToString());
		}
	}
}

