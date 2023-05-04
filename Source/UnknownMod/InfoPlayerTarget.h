// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InfoPlayerTarget.generated.h"

UCLASS()
class UNKNOWNMOD_API AInfoPlayerTarget : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInfoPlayerTarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Jump();
	void StopJumping();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};