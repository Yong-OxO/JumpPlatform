// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "DefaultInputDataAsset.generated.h"



UCLASS()
class JUMPPLATFORM_API UDefaultInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "UInputMapingContext")
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "InputAction")
	UInputAction* MoveAction = nullptr;	

	UPROPERTY(EditAnywhere, Category = "InputAction")
	UInputAction* LookAction = nullptr;	

	UPROPERTY(EditAnywhere, Category = "InputAction")
	UInputAction* JumpAction = nullptr;	

	UPROPERTY(EditAnywhere, Category = "InputAction")
	UInputAction* CrouchAction = nullptr;	

	UPROPERTY(EditAnywhere, Category = "InputAction")
	UInputAction* ZoomWheelAction = nullptr;	
};
