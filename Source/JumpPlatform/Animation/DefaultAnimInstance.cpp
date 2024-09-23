// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DefaultAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UDefaultAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		check(false);
		return;
	}
	else if (!Pawn) { return; }

	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);
}

void UDefaultAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent) { return; }

	Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);

	bShouldMove = !FMath::IsNearlyZero(Speed);

	bIsCrouch = MovementComponent->IsCrouching();
	bIsFalling = MovementComponent->IsFalling();
}
