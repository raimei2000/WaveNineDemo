#include "Trap.h"
#include "Components/DecalComponent.h"

ATrap::ATrap()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);

	WarningDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("WarningDecal"));
	WarningDecal->SetupAttachment(SceneRoot);

	//PrimaryActorTick.bCanEverTick = true;
	TriggerDelay = 0.f;
	AffectRadius = 0.f;
	Damage = 0.f;
}

void ATrap::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TriggerTimerHandle, this, &ATrap::TriggerTrap, TriggerDelay, false);
}

void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), AffectRadius, 14, FColor::Black);
}

void ATrap::TriggerTrap()
{

}

void ATrap::DestroyTrap()
{
	Destroy();
}
