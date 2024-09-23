// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

class USoftWheelSpringArmComponent;
class UDefaultAnimInstance;
class UCameraComponent;


UCLASS()
class JUMPPLATFORM_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = "MovementComponent")
	FRotator RotationRate = FRotator(0.0, 720.0, 0.0);
	UPROPERTY(EditAnywhere, Category = "MovementComponent")
	bool bOrientRotationToMovement = true;
	UPROPERTY(EditAnywhere, Category = "MovementComponent")
	bool bCanCrouch = true;

public:
	UPROPERTY(EditAnywhere, Category = "CapsuleComponent")
	float CapsuleHalfHeight = 100.f;


public:
	UPROPERTY(EditAnywhere, Category = "SkeletalMeshComponent")
	USkeletalMesh* SkeletalMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "SkeletalMeshComponent")
	TSubclassOf<UDefaultAnimInstance> AnimClass = nullptr;
	UPROPERTY(EditAnywhere, Category = "SkeletalMeshComponent")
	FTransform SkeletalMeshTransform;

public:
	UPROPERTY(EditAnywhere, Category = "SpringArm")
	FTransform SpringArmTransform;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USoftWheelSpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;
};
