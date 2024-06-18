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
struct FInputActionValue;
class UOxygenComponent;
class AProyectoIntermedio3GameMode;

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

	AProyectoIntermedio3GameMode* CurrentGameMode = nullptr;

	//Animation montage for attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackParams", meta = (AllowPrivateAccess = "true"))
	float attackCooldown;

	UFUNCTION()
	void PerformAttackNotifyAnim();

	UFUNCTION()
	void TakeDamageFromAI(int32 damageAmmount);

	UPROPERTY()
	FOnTakeDamage OnTakeDamage;

private:
	UPROPERTY()
	UAttackComponent* AttackComponent = nullptr;

	UPROPERTY()
	bool canAttack = true;

	UPROPERTY()
	float actualTimeAttackColdown;

public:
	AProyectoIntermedio3Character();
	
	UPROPERTY()
	UOxygenComponent* OxygenComponent = nullptr;

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void Tick(float DeltaTime);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

