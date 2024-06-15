#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "CharacterStore.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AStore_GameMode;

UCLASS()
class PROYECTOINTERMEDIO3_API ACharacterStore : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	AStore_GameMode* CurrentGameMode = nullptr;

public:
	ACharacterStore();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

private:
	void CheckMovementLimitToCamera();

public:	
	virtual void Tick(float DeltaTime) override;

	void UpdateAnimFloatVariable(float NewValue);
};
