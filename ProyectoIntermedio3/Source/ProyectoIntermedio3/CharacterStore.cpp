#include "CharacterStore.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Store_GameMode.h"
#include "AB_StoreDiver.h"
#include "InventoryComponent.h"
#include "Store_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Interactable.h"
#include <Kismet/KismetSystemLibrary.h>

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

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
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
			//Movement started-> configuration pressed
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterStore::Move);

			//Movement completed-> configuration released
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACharacterStore::FinishMove);

			
			//Interact
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACharacterStore::Interact);
		}
	}

void ACharacterStore::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	
	UE_LOG(LogTemp, Warning, TEXT("MovementVector: %f"), MovementVector.X);
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

			//animation of walking ans speed at 1
			// Access and update the animation instance
			if (USkeletalMeshComponent* MeshComp = GetMesh())
			{
				if (UAB_StoreDiver* AnimInstance = Cast<UAB_StoreDiver>(MeshComp->GetAnimInstance()))
				{
					AnimInstance->UpdateSpeedVariable(MovementVector.X); // Example of updating the variable
				}
			}
		}

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacterStore::FinishMove(const FInputActionValue& Value)
{
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		if (UAB_StoreDiver* AnimInstance = Cast<UAB_StoreDiver>(MeshComp->GetAnimInstance()))
		{
			AnimInstance->UpdateSpeedVariable(0); // Example of updating the variable
		}
	}
}

void ACharacterStore::CheckMovementLimitToCamera()
{
	FVector CharacterPosition = GetActorLocation();

	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (CameraManager)
	{
		FVector CameraPosition = CameraManager->GetCameraLocation();

		float MinX = CameraPosition.X - 250;
		float MaxX = CameraPosition.X + 250;

		CharacterPosition.X = FMath::Clamp(CharacterPosition.X, MinX, MaxX);

		SetActorLocation(CharacterPosition);
	}
}

void ACharacterStore::Interact()
{
	if (!bDetectItem || !DetectedActor)
	{
		return;
	}

	// Check if implements interface
	if(UKismetSystemLibrary::DoesImplementInterface(DetectedActor, UInteractable::StaticClass()))
		IInteractable::Execute_Interact(DetectedActor);
}

void ACharacterStore::DetectInteractable()
{
	const FVector Start = GetActorLocation() + FVector(0.f, 0.f, 50.f);
	const FVector ForwardDirection = GetActorForwardVector();
	const FVector End = Start + ForwardDirection * 200.f;
	FHitResult Hit;

	FVector BoxHalfSize(50.f, 50.f, 50.f);

	bool bHit = UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxHalfSize,
		FRotator::ZeroRotator,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None, 
		Hit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.0f
	);

	if (bHit)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (UKismetSystemLibrary::DoesImplementInterface(HitActor, UInteractable::StaticClass()))
			{
				bDetectItem = true;
				DetectedActor = HitActor;
				FString InteractionText = IInteractable::Execute_GetInteractionText(HitActor);
				OnInteract.ExecuteIfBound(InteractionText);
				return;
			}
		}
	}

	bDetectItem = false;
	DetectedActor = nullptr;
	OnInteract.ExecuteIfBound("");
}

void ACharacterStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckMovementLimitToCamera();

	DetectInteractable();
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

