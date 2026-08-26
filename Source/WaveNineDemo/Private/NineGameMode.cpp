#include "NineGameMode.h"
#include "NineCharacter.h"
#include "NinePlayerController.h"
#include "NineGameState.h"

ANineGameMode::ANineGameMode()
{
    DefaultPawnClass = ANineCharacter::StaticClass();
    PlayerControllerClass = ANinePlayerController::StaticClass();
    GameStateClass = ANineGameState::StaticClass();
}
