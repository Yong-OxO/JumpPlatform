// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DefaultAnimInstance.generated.h"

class UPawnMovementComponent;

UCLASS()
class JUMPPLATFORM_API UDefaultAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly)
	double Speed = 0.0;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsCrouch = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
	
};
