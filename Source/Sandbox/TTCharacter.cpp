// Fill out your copyright notice in the Description page of Project Settings.

#include "TTCharacter.h"
#include "TTAnimInstance.h"

// Sets default values
ATTCharacter::ATTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

    SpringArm->SetupAttachment(GetCapsuleComponent());
    Camera->SetupAttachment(SpringArm);

    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
    SpringArm->TargetArmLength = 400.0f;
    SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

    // SkeletalMesh'/Game/ParagonDekker/Characters/Heroes/Dekker/Meshes/Dekker.Dekker'
    // SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC'
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_PARAGON(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC"));
    if (SK_PARAGON.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(SK_PARAGON.Object);
    }

    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

    // AnimBlueprint'/Game/AnimBP/Dekker/DekkerBlueprint.DekkerBlueprint'
    // AnimBlueprint'/Game/AnimBP/Gwang/KwangBlueprint.KwangBlueprint'
    static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_PARAGON(TEXT("/Game/AnimBP/Gwang/KwangBlueprint.KwangBlueprint_C"));
    if (ANIM_PARAGON.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(ANIM_PARAGON.Class);
    }

    SetControlMode();
}

// Called when the game starts or when spawned
void ATTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATTCharacter::SetControlMode()
{
    SpringArm->TargetArmLength = 450.0f;
    SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bInheritPitch = true;
    SpringArm->bInheritRoll = true;
    SpringArm->bInheritYaw = true;
    SpringArm->bDoCollisionTest = true;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

// Called every frame
void ATTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ATTCharacter::UpDown);
    PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ATTCharacter::LeftRight);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATTCharacter::LookUp);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATTCharacter::Turn);
    PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ATTCharacter::Attack);
}

void ATTCharacter::UpDown(float NewAxisValue)
{
    auto AnimInstance = Cast<UTTAnimInstance>(GetMesh()->GetAnimInstance());
    if(!AnimInstance->CanCharacterMove())
        AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void ATTCharacter::LeftRight(float NewAxisValue)
{
    auto AnimInstance = Cast<UTTAnimInstance>(GetMesh()->GetAnimInstance());
    if (!AnimInstance->CanCharacterMove())
        AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void ATTCharacter::Turn(float NewAxisValue)
{
    AddControllerYawInput(NewAxisValue);
}

void ATTCharacter::LookUp(float NewAxisValue)
{
    AddControllerPitchInput(NewAxisValue);
}

void ATTCharacter::Attack()
{
    auto AnimInstance = Cast<UTTAnimInstance>(GetMesh()->GetAnimInstance());
    if(nullptr == AnimInstance) return;

    AnimInstance->OrderAttack();
}



