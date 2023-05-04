// Fill out your copyright notice in the Description page of Project Settings.

#include "InfoPlayerTarget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AInfoPlayerTarget::AInfoPlayerTarget()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(46.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.11f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(60);

	bDead = false;

}
// Called when the game starts or when spawned
void AInfoPlayerTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInfoPlayerTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInfoPlayerTarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AInfoPlayerTarget::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AInfoPlayerTarget::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AInfoPlayerTarget::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInfoPlayerTarget::MoveRight);

}
void AInfoPlayerTarget::MoveForward(float Axis)
{
	if ((Controller != NULL) && (Axis != 0.0f) && (bDead != true)) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void AInfoPlayerTarget::MoveRight(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void AInfoPlayerTarget::Jump()
{
	if ((Controller != NULL) && (bDead != true)) 
	{
		ACharacter::Jump();
	}
}

void AInfoPlayerTarget::StopJumping()
{
	if ((Controller != NULL) && (bDead != true))
	{
		ACharacter::StopJumping();
	}
}
