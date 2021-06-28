// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "TTAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API UTTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    UTTAnimInstance();
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
// UFUNCTION
    UFUNCTION()
    void AnimNotify_CheckAttackEnd();

    UFUNCTION()
    void AnimNotify_AttackRecovery();

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
    float CurrentPawnSpeed;
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    bool IsAttack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    int CurrentCombo;

    UPROPERTY()
    int MaxCombo = 4;

    UPROPERTY()
    bool OrderNextAttack = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    bool CanAttack = true;

public:
    // Order External Class
    void OrderAttack();

    bool  CanCharacterMove() { return IsAttack; }
};
