#include "EnemySpawner.h"
#include "AIEnemyCharacterBase.h"
#include "AIEnemyControllerBase.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	RootCmp = CreateDefaultSubobject<USceneComponent>(TEXT("RootCmp"));
	SetRootComponent(RootCmp);

	ArrowCmp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowCmp->SetupAttachment(RootCmp);

	SpawnSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnSphere"));
	SpawnSphere->SetupAttachment(RootCmp);

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (!world)
		return;

	int randomSpawn = FMath::RandRange(0, 3);
	if (randomSpawn > 0)
		return;

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	int randomFish = FMath::RandRange(0, 2);
	AAIEnemyCharacterBase* MyEnemy = world->SpawnActor<AAIEnemyCharacterBase>(randomFish == 2 ? BP_SharkEnemy : BP_PiranhaEnemy, SpawnLocation, SpawnRotation, SpawnParams);

	AAIEnemyControllerBase* MyEnemyController = world->SpawnActor<AAIEnemyControllerBase>(BP_EnemyController, SpawnLocation, SpawnRotation, SpawnParams);
	if(MyEnemyController)
	{
		MyEnemyController->Possess(MyEnemy);
		if (BP_BehaviourTree)
		{
			MyEnemyController->RunBehaviorTree(BP_BehaviourTree);
		}
	}
}

