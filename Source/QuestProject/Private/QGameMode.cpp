#include "QGameMode.h"
#include "QCharacter.h"
#include "QPlayerController.h"

AQGameMode::AQGameMode()
{
	DefaultPawnClass = AQGameMode::StaticClass();
	PlayerControllerClass = AQGameMode::StaticClass();
}
