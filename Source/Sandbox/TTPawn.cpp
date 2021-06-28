// Fill out your copyright notice in the Description page of Project Settings.

#include "TTPawn.h"

// Sets default values
ATTPawn::ATTPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
    Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
    SpringArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

    RootComponent = Capsule;
    Mesh->SetupAttachment(Capsule);
    SpringArm->SetupAttachment(Capsule);
    Camera->SetupAttachment(SpringArm);

    Capsule->SetCapsuleHalfHeight(88.0f);
    Capsule->SetCapsuleRadius(34.0f);
    Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
    SpringArm->TargetArmLength = 400.0f;
    SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
    
    // SkeletalMesh'/Game/ParagonDekker/Characters/Heroes/Dekker/Meshes/Dekker.Dekker'
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_PARAGON(TEXT("/Game/ParagonDekker/Characters/Heroes/Dekker/Meshes/Dekker.Dekker"));
    if (SK_PARAGON.Succeeded())
    {
        Mesh->SetSkeletalMesh(SK_PARAGON.Object);
    }

    Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

    // AnimBlueprint'/Game/AnimBP/Dekker/DekkerBlueprint.DekkerBlueprint'
    static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_PARAGON(TEXT("/Game/AnimBP/Dekker/DekkerBlueprint.DekkerBlueprint_C"));
    if (ANIM_PARAGON.Succeeded())
    {
        Mesh->SetAnimInstanceClass(ANIM_PARAGON.Class);
    }
}

// Called when the game starts or when spawned
void ATTPawn::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ATTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ATTPawn::UpDown);
    PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ATTPawn::LeftRight);
    
}

void ATTPawn::UpDown(float NewAxisValue)
{
    AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void ATTPawn::LeftRight(float NewAxisValue)
{
    AddMovementInput(GetActorRightVector(), NewAxisValue);
}

