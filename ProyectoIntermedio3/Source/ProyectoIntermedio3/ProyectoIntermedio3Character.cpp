#include "ProyectoIntermedio3Character.h"

#include "AB_GameDiver.h"
#include "AttackComponent.h"
#include "AudioManager.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "OxygenComponent.h"
#include "ShieldComponent.h"
#include "ProyectoIntermedio3GameMode.h"

#include "Proyecto3PlayerController.h"
#include "Store_PlayerController.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProyectoIntermedio3Character

AProyectoIntermedio3Character::AProyectoIntermedio3Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = false; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

	OxygenComponent = CreateDefaultSubobject<UOxygenComponent>(TEXT("OxygenComponent"));
	ShieldComponent = CreateDefaultSubobject<UShieldComponent>(TEXT("ShieldComponent"));
}

void AProyectoIntermedio3Character::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<AProyecto3PlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	CurrentGameMode = Cast<AProyectoIntermedio3GameMode>(GetWorld()->GetAuthGameMode());

	InitializeAudioManager();

	MakeSound("Click_on_Button");
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProyectoIntermedio3Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProyectoIntermedio3Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProyectoIntermedio3Character::Look);

		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProyectoIntermedio3Character::Attack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProyectoIntermedio3Character::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);

		if (MovementVector.X != 0.0f)
		{
			FVector Scale = GetActorScale3D();
			Scale.Y = FMath::Sign(MovementVector.X) * FMath::Abs(Scale.Y);
			SetActorScale3D(Scale);
		}
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProyectoIntermedio3Character::Look(const FInputActionValue& Value)
{
	//// input is a Vector2D
	//FVector2D LookAxisVector = Value.Get<FVector2D>();

	//if (Controller != nullptr)
	//{
	//	// add yaw and pitch input to controller
	//	AddControllerYawInput(LookAxisVector.X);
	//	AddControllerPitchInput(LookAxisVector.Y);
	//}
}

void AProyectoIntermedio3Character::Attack(const FInputActionValue& Value)
{
	if(canAttack)
	{
		AttackComponent = GetComponentByClass<UAttackComponent>();
		if (AttackComponent)
		{
			//anim montage
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if(AnimInstance && AttackMontage)
			{
				AnimInstance->Montage_Play(AttackMontage);
			}

			//quit access to attack
			canAttack = false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InteractionComponent not found!"));
		}
	}
	
}

void AProyectoIntermedio3Character::PerformAttackNotifyAnim()
{
	//attacks
	if(canAttack)
	{
		AttackComponent->PerformRaycast();
	}
}

void AProyectoIntermedio3Character::TakeDamageFromAI(int32 damageAmmount)
{
	if (ShieldComponent->GetShield() > 0)
	{
		ShieldComponent->RemoveShield(1);
	}
	else
	{
		OxygenComponent->SetCurrentOxygen(OxygenComponent->GetOxygen() - damageAmmount);
	}

	UE_LOGFMT(LogTemp, Log, "Current Oxigen: {0}", OxygenComponent->GetOxygen());

	OnTakeDamage.Broadcast();
}

void AProyectoIntermedio3Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(actualTimeAttackColdown >= attackCooldown)
	{
		//can attack when cooldown pass
		canAttack = true;
		//restart timer
		actualTimeAttackColdown = 0;
	}
	else
	{
		//add time
		actualTimeAttackColdown+= DeltaTime;
	}
}

void AProyectoIntermedio3Character::InitializeAudioManager()
{
	if (BP_AudioManager)
	{
		// Spawn the AudioManager instance
		AudioManagerInstance = GetWorld()->SpawnActor<AAudioManager>(BP_AudioManager);

		if (!AudioManagerInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn AudioManager instance!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BP_AudioManager is not set!"));
	}
}

void AProyectoIntermedio3Character::DeathPlayer()
{
	//anim montage
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage);
		DisableMovement();
		OnDeathAnimationFinished();
		
	}
}

void AProyectoIntermedio3Character::DisableMovement()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->SetMovementMode(MOVE_None);
	}
}

//quits all the animation to stay the death pose
void AProyectoIntermedio3Character::OnDeathAnimationFinished()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	//Cast to the specific anim instance class and set the bIsDead variable
	if (UAB_GameDiver* ABInstance = Cast<UAB_GameDiver>(AnimInstance))
	{
		ABInstance->Death();  // Set this to true to prevent idle animation
	}
}

void AProyectoIntermedio3Character::MakeSound(FString nameSound)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound = AudioManagerInstance->FindSoundByName(nameSound);
		if (Sound)
		{
			AudioManagerInstance->PlaySound(Sound);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sound not found in AudioManager!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioManager instance is null!"));
	}
}

