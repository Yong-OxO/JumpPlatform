// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"



class ADefaultCharacter;
class UDefaultInputDataAsset;
struct FInputActionValue;


UCLASS()
class JUMPPLATFORM_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADefaultPlayerController();

public:
	UPROPERTY(EditAnywhere, Category = "Input")
	UDefaultInputDataAsset* InputDataAsset = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	ADefaultCharacter* ControlledCharacter = nullptr;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OnStopJump(const FInputActionValue& InputActionValue);
	void OnCrouch(const FInputActionValue& InputActionValue);
	void OnStopCrouch(const FInputActionValue& InputActionValue);
	void OnZoomWheel(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY(EditAnywhere)
	float LookRotationRate = 0.5f;


	
};
