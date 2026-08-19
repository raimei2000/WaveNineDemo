// Fill out your copyright notice in the Description page of Project Settings.


#include "NineGameMode.h"
#include "NineCharacter.h"
#include "NinePlayerController.h"

ANineGameMode::ANineGameMode()
{
    DefaultPawnClass = ANineCharacter::StaticClass();
    PlayerControllerClass = ANinePlayerController::StaticClass();
}
