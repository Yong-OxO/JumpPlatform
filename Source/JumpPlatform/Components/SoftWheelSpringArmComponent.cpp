// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SoftWheelSpringArmComponent.h"

void USoftWheelSpringArmComponent::OnZoomWheel(const float InputActionValue)
{
	DesiredTargetArmLength = FMath::Clamp(DesiredTargetArmLength + InputActionValue, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::SetMinMaxTargetArmLength(const float MinLength, const float MaxLength)
{
	if (MinLength > MaxLength)
	{
		check(nullptr);
		return;
	}

	MinTargetArmLength = MinLength;
	MaxTargetArmLength = MaxLength;

	TargetArmLength = FMath::Clamp(TargetArmLength, MinTargetArmLength, MaxTargetArmLength);
	DesiredTargetArmLength = TargetArmLength;
}

void USoftWheelSpringArmComponent::UpdateDesiredTargetArmLength(const float DeltaTime)
{
	if (FMath::IsNearlyEqual(TargetArmLength, DesiredTargetArmLength)) { return; }

	const float DeltaSpeed = FMath::Clamp(DeltaTime * WheelSpeed, 0.f, 1.f);
	TargetArmLength = FMath::Lerp(TargetArmLength, DesiredTargetArmLength, DeltaSpeed);
	TargetArmLength = FMath::Clamp(TargetArmLength, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateDesiredTargetArmLength(DeltaTime);
}
