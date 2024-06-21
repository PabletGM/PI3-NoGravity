#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "GameFramework/Character.h"

#include "CharacterStore.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AStore_GameMode;

DECLARE_DYNAMIC_DELEGATE_OneParam(FInteractDelegate, FString, text);


UCLASS()
class PROYECTOINTERMEDIO3_API ACharacterStore : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

public:
	ACharacterStore();

	UPROPERTY()
	FInteractDelegate OnInteract;

	UPROPERTY()
	UInventoryComponent* InventoryComponent = nullptr;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void FinishMove(const FInputActionValue& Value);

	void Interact();

	void Tick(float DeltaTime);

private:
	void CheckMovementLimitToCamera();

	//Interact variables
	bool bDetectItem = false;
	AActor* DetectedActor = nullptr;
	void DetectInteractable();

public:	
	void UpdateAnimFloatVariable(float NewValue);
};
