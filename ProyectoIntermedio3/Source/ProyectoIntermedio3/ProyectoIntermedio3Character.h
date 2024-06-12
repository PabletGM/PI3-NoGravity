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
DECLARE_DYNAMIC_DELEGATE_OneParam(FInteractDelegate, FString, text);

UCLASS(config=Game)
class AProyectoIntermedio3Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Attack Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	AProyectoIntermedio3GameMode* CurrentGameMode = nullptr;

	// Animation montage for attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
public:
	UFUNCTION()
	void PerformAttackNotifyAnim();

private:
	UPROPERTY()
	UAttackComponent* AttackComponent = nullptr;

	//Interact variables
	bool bDetectItem = false;
	AActor* DetectedActor = nullptr;
	void DetectInteractable();

	UPROPERTY()
	bool canAttack = true;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackParams", meta = (AllowPrivateAccess = "true"))
	float attackCooldown;

private:
	UPROPERTY()
	float actualTimeAttackColdown;
	

public:
	AProyectoIntermedio3Character();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UOxygenComponent* OxygenComponent;

	UPROPERTY()
	FInteractDelegate OnInteract;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void Attack(const FInputActionValue& Value);

	void Interact();

	void Tick(float DeltaTime);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

