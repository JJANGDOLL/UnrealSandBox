// Fill out your copyright notice in the Description page of Project Settings.

#include "TTPlayerController.h"

void ATTPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
}


