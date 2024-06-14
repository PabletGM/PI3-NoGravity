// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStore.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Store_GameMode.h"

#include "AB_StoreDiver.h"
#include "Store_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterStore::ACharacterStore()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	
	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	// GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	// GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

// Called when the game starts or when spawned
void ACharacterStore::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<AStore_PlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Cast to GameMode for update the variable with it
	CurrentGameMode = Cast<AStore_GameMode>(GetWorld()->GetAuthGameMode());
	
}

void ACharacterStore::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// // get forward vector
		// const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		// AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// Called every frame
void ACharacterStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterStore::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterStore::Move);
	}
	

}

void ACharacterStore::UpdateAnimFloatVariable(float NewValue)
{
	//access to mesh
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		//see if its animInstance
		if (UAB_StoreDiver* AnimInstance = Cast<UAB_StoreDiver>(MeshComp->GetAnimInstance()))
		{
			//update speed
			AnimInstance->UpdateSpeedVariable(NewValue);
		}
	}
}

