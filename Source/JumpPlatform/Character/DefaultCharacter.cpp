
#include "Character/DefaultCharacter.h"
#include "Animation/DefaultAnimInstance.h"
#include "Components/SoftWheelSpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ADefaultCharacter::ADefaultCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjectFinder(TEXT("/ Script / Engine.SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith'"));
	check(ObjectFinder.Object);
	SkeletalMesh = ObjectFinder.Object;

	PrimaryActorTick.bCanEverTick = true;
	
	{
		const FRotator Rotation = FRotator(0., -90.0, 0.);
		const FVector Translation = FVector(0., 0., -90.0);
		SkeletalMeshTransform = FTransform(Rotation, Translation, FVector::OneVector);
	}
	{
		const FRotator Rotation = FRotator(0., 90.0, 0.);
		const FVector Translation = FVector(0., 0., 90.0);
		SpringArmTransform = FTransform(Rotation, Translation, FVector::OneVector);
	}

	SpringArm = CreateDefaultSubobject<USoftWheelSpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	{
		SpringArm->SetupAttachment(GetMesh());
		SpringArm->ProbeSize = 5.0;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
		SpringArm->SetMinMaxTargetArmLength(200.f, SpringArm->GetMaxTargetArmLength());
	}
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	{
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		Movement->RotationRate = RotationRate;
		Movement->bOrientRotationToMovement = bOrientRotationToMovement;
		Movement->GetNavAgentPropertiesRef().bCanCrouch = bCanCrouch;

		const float NewCapsuleHalfHeight = CapsuleHalfHeight * 0.5f;
		Movement->SetCrouchedHalfHeight(NewCapsuleHalfHeight);
	}
	{
		UCapsuleComponent* Capsule = GetCapsuleComponent();
		if (!FMath::IsNearlyEqual(Capsule->GetUnscaledCapsuleHalfHeight(), CapsuleHalfHeight))
		{
			Capsule->SetCapsuleHalfHeight(CapsuleHalfHeight, false);
		}
	}
	{
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		SkeletalMeshComponent->SetAnimClass(AnimClass);

		SpringArm->SetRelativeTransform(SpringArmTransform);
	}
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

