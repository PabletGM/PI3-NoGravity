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
#include "InventoryComponent.h"
#include "Proyecto3PlayerController.h"
#include "Logging/StructuredLog.h"
#include "GameInstanceNoGravity.h"
#include <Kismet/GameplayStatics.h>

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
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	GameInstance = Cast<UGameInstanceNoGravity>(UGameplayStatics::GetGameInstance(GetWorld()));
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

	if (GameInstance)
	{
		if(GameInstance->PlayerDataAsset)
			GetCharacterMovement()->MaxWalkSpeed = GameInstance->PlayerDataAsset->PlayerData.MaxWalkSpeed;
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Cant initialize player data"));
	}

	if (GameInstance && InventoryComponent)
	{
		GameInstance->RestoreInventoryIcons(InventoryComponent);
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &AProyectoIntermedio3Character::PostBeginPlay);
	
}

void AProyectoIntermedio3Character::PostBeginPlay()
{
	InitializeAudioManager();
	MakeMusic("musicOcean");
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

AAudioManager* AProyectoIntermedio3Character::GetAudioManagerInstance() const
{
	return AudioManagerInstance;
}

void AProyectoIntermedio3Character::Move(const FInputActionValue& Value)
{

	//if its not dead
	if(!isDead)
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
	
}

void AProyectoIntermedio3Character::Look(const FInputActionValue& Value)
{
	
}

void AProyectoIntermedio3Character::Attack(const FInputActionValue& Value)
{
	//if its not dead
	if(!isDead)
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
					//quit access to attack
					canAttack = false;
					//AnimInstance->Montage_Play(AttackMontage);
					AnimInstance->Montage_Play(AttackMontage, AttackSpeed);
				}
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("InteractionComponent not found!"));
		}
	}
}

void AProyectoIntermedio3Character::PerformAttackNotifyAnim()
{
	//attacks
	canAttack = true;
	AttackComponent->PerformRaycast();
}

void AProyectoIntermedio3Character::TakeDamageFromAI(int32 damageAmmount)
{
	//if its not dead
	if(!isDead)
	{
		if (ShieldComponent->GetShield() > 0)
		{
			ShieldComponent->RemoveShield(1);
		}
		else
		{
			OxygenComponent->SetCurrentOxygen(OxygenComponent->GetOxygen() - damageAmmount);
		}

		//UE_LOGFMT(LogTemp, Log, "Current Oxigen: {0}", OxygenComponent->GetOxygen());

		OnTakeDamage.Broadcast();

		MakeSoundEffect2("playerHurt");
		MakeSoundEffect("bite2");
	}
}

void AProyectoIntermedio3Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	
}

void AProyectoIntermedio3Character::InitializeAudioManager()
{
	if (BP_AudioManager)
	{
		// Spawn the AudioManager instance
		AudioManagerInstance = GetWorld()->SpawnActor<AAudioManager>(BP_AudioManager);

		//add a tag to the AudioManager
		if (AudioManagerInstance)
		{
			// Assign a unique tag to the AudioManager instance
			AudioManagerInstance->Tags.Add(FName("AudioManager"));
		}
		
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
		MakeSoundEffect2("drownGameOver");
		//player died notification
		isDead = true;
	}
}

void AProyectoIntermedio3Character::DisableMovement()
{
	if (GetCharacterMovement())
		GetCharacterMovement()->SetMovementMode(MOVE_None);
}

//quits all the animation to stay the death pose
void AProyectoIntermedio3Character::OnDeathAnimationFinished()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	//Cast to the specific anim instance class and set the bIsDead variable
	if (UAB_GameDiver* ABInstance = Cast<UAB_GameDiver>(AnimInstance))
		ABInstance->Death();  // Set this to true to prevent idle animation
}

void AProyectoIntermedio3Character::MakeSoundEffect(FString nameSound)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Music = AudioManagerInstance->FindSoundByName(nameSound);
		if (Music)
		{
			AudioManagerInstance->PlaySoundEffect1(Music);
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

void AProyectoIntermedio3Character::MakeSoundEffect2(FString nameSound2)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound = AudioManagerInstance->FindSoundByName(nameSound2);
		if (Sound)
		{
			AudioManagerInstance->PlaySoundEffect2(Sound);
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

void AProyectoIntermedio3Character::MakeMusic(FString nameMusic)
{
	if (AudioManagerInstance)
	{
		// Example method call on AudioManagerInstance
		// Replace PlaySound with your actual method name and parameters
		USoundBase* Sound2 = AudioManagerInstance->FindSoundByName(nameMusic);
		if (Sound2)
		{
			AudioManagerInstance->PlayMusic(Sound2);
		}
		else
		{
			// UE_LOG(LogTemp, Warning, TEXT("Sound not found in AudioManager!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioManager instance is null!"));
	}
}