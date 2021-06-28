// Fill out your copyright notice in the Description page of Project Settings.

#include "TTAnimInstance.h"

UTTAnimInstance::UTTAnimInstance()
{
    CurrentPawnSpeed = 0.0f;
    IsAttack = false;
}

void UTTAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    auto Pawn = TryGetPawnOwner();
    if (::IsValid(Pawn))
    {
        CurrentPawnSpeed = Pawn->GetVelocity().Size();
    }
}

void UTTAnimInstance::AnimNotify_CheckAttackEnd()
{
    if (OrderNextAttack)
    {
        CurrentCombo++;
        OrderNextAttack = false;
        return;
    }
    IsAttack = false;
    CanAttack = false;
}

void UTTAnimInstance::AnimNotify_AttackRecovery()
{
    if(IsAttack)
        IsAttack = false;
    CurrentCombo = 0;
    CanAttack = true;
}

void UTTAnimInstance::OrderAttack()
{
    if(CanAttack ==false)
        return;

    if (CurrentCombo == 3)
    {
        OrderNextAttack = false;
        return;
    }

    if (!IsAttack)
    {
        IsAttack = true;
    }
    else
    {
        OrderNextAttack = true;
    }
}

