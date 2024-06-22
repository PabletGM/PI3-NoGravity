#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "ProyectoIntermedio3Character.generated.h"

class AProyectoIntermedio3GameMode;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UOxygenComponent;
class UShieldComponent;
class UInventoryComponent;
class AAudioManager;
class AProyectoIntermedio3GameMode;
class UGameInstanceNoGravity;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamage);

UCLASS(config=Game)
class AProyectoIntermedio3Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	//Animation montage for attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	//Animation montage for death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathMontage;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackParams", meta = (AllowPrivateAccess = "true"))
	float AttackSpeed = 0.0f;

	UFUNCTION()
	void PerformAttackNotifyAnim();

	UFUNCTION()
	void TakeDamageFromAI(int32 damageAmmount);

	UFUNCTION()
	void DeathPlayer();

	// Function to disable movement
	UFUNCTION()
	void DisableMovement();

	// Function to handle end of death animation
	UFUNCTION()
	void OnDeathAnimationFinished();

	UFUNCTION()
	void MakeSoundEffect(FString nameSound);

	UFUNCTION()
	void MakeSoundEffect2(FString nameSound2);

	UFUNCTION()
	void MakeMusic(FString nameMusic);

	UPROPERTY()
	FOnTakeDamage OnTakeDamage;

	UPROPERTY()
	bool isDead = false;

private:
	UGameInstanceNoGravity* GameInstance;

	UPROPERTY()
	UAttackComponent* AttackComponent = nullptr;

	UPROPERTY()
	bool canAttack = true;

public:
	AProyectoIntermedio3Character();
	
	UPROPERTY()
	UOxygenComponent* OxygenComponent = nullptr;

	UPROPERTY()
	UShieldComponent* ShieldComponent = nullptr;

	UPROPERTY()
	UInventoryComponent* InventoryComponent = nullptr;

	// Reference to the AudioManager
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TSubclassOf<AAudioManager> BP_AudioManager;

	// Reference to the instantiated AudioManager
	UPROPERTY()
	AAudioManager* AudioManagerInstance;

	UFUNCTION(BlueprintCallable, Category = "Audio")
	AAudioManager* GetAudioManagerInstance() const;

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void Tick(float DeltaTime);

	void InitializeAudioManager();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay();

	void PostBeginPlay();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

