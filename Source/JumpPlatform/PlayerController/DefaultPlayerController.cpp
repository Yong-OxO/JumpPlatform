// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/DefaultPlayerController.h"
#include "Character/DefaultCharacter.h"
#include "PlayerController/DefaultInputDataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputActionValue.h"
#include "Components/SoftWheelSpringArmComponent.h"


ADefaultPlayerController::ADefaultPlayerController()
{

}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(InputDataAsset->InputMappingContext, 0);
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(InputDataAsset->MoveAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnMove);
	EnhancedInputComponent->BindAction(InputDataAsset->LookAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnLook);
	EnhancedInputComponent->BindAction(InputDataAsset->JumpAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnJump);
	EnhancedInputComponent->BindAction(InputDataAsset->JumpAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnStopJump);
	EnhancedInputComponent->BindAction(InputDataAsset->CrouchAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnCrouch);
	EnhancedInputComponent->BindAction(InputDataAsset->CrouchAction, ETriggerEvent::Completed, this, &ADefaultPlayerController::OnStopCrouch);
	EnhancedInputComponent->BindAction(InputDataAsset->ZoomWheelAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::OnZoomWheel);

}

void ADefaultPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());

	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator RotationYaw = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(RotationYaw);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(RotationYaw);

	ControlledCharacter->AddMovementInput(ForwardVector, ActionValue.X);
	ControlledCharacter->AddMovementInput(RightVector, ActionValue.Y);
}

void ADefaultPlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	AddYawInput(ActionValue.X * LookRotationRate);
	AddPitchInput(ActionValue.Y * LookRotationRate);
}

void ADefaultPlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	ControlledCharacter->Jump();
}

void ADefaultPlayerController::OnStopJump(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	ControlledCharacter->StopJumping();
}

void ADefaultPlayerController::OnCrouch(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	ControlledCharacter->Crouch();
}

void ADefaultPlayerController::OnStopCrouch(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	ControlledCharacter->UnCrouch();
}

void ADefaultPlayerController::OnZoomWheel(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());

	USoftWheelSpringArmComponent* SpringArm = ControlledCharacter->GetComponentByClass<USoftWheelSpringArmComponent>();
	if (!SpringArm) 
	{ 
		ensure(false); 
		return; 
	}

	const float ActionValue = InputActionValue.Get<float>();
	if (FMath::IsNearlyZero(ActionValue)) { return; }
	SpringArm->OnZoomWheel(ActionValue * 20.f);
}


