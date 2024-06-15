#include "CharacterStore.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Store_GameMode.h"
#include "AB_StoreDiver.h"
#include "Store_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

ACharacterStore::ACharacterStore()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 80.f);
	
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void ACharacterStore::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<AStore_PlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	CurrentGameMode = Cast<AStore_GameMode>(GetWorld()->GetAuthGameMode());
}

void ACharacterStore::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Movement
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterStore::Move);
	}
}

void ACharacterStore::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if (MovementVector.X != 0.0f)
		{
			FVector Scale = GetActorScale3D();
			Scale.Y = FMath::Sign(MovementVector.X) * FMath::Abs(Scale.Y);
			SetActorScale3D(Scale);
		}

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterStore::CheckMovementLimitToCamera()
{
	FVector CharacterPosition = GetActorLocation();

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (CameraManager)
	{
		FVector CameraPosition = CameraManager->GetCameraLocation();

		float MinX = CameraPosition.X - 350;
		float MaxX = CameraPosition.X + 350;

		CharacterPosition.X = FMath::Clamp(CharacterPosition.X, MinX, MaxX);

		SetActorLocation(CharacterPosition);
	}
}

void ACharacterStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckMovementLimitToCamera();
}

void ACharacterStore::UpdateAnimFloatVariable(float NewValue)
{
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		if (UAB_StoreDiver* AnimInstance = Cast<UAB_StoreDiver>(MeshComp->GetAnimInstance()))
		{
			AnimInstance->UpdateSpeedVariable(NewValue);
		}
	}
}

