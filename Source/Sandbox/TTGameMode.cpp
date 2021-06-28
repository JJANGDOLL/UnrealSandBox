// Fill out your copyright notice in the Description page of Project Settings.

#include "TTGameMode.h"
#include "TTCharacter.h"
#include "TTPlayerController.h"

ATTGameMode::ATTGameMode()
{
    DefaultPawnClass = ATTCharacter::StaticClass(); 
    PlayerControllerClass = ATTPlayerController::StaticClass();
}
