#include "Trap.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NineCharacter.h"

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
	if (ActivationSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ActivationSound,
			GetActorLocation()
		);
	}

	TArray<AActor*> Hits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	UKismetSystemLibrary::SphereOverlapActors(
		this, GetActorLocation(), AffectRadius,
		ObjectTypes, ANineCharacter::StaticClass(), TArray<AActor*> {this}, Hits);

	for (AActor* Hit : Hits)
	{
		UGameplayStatics::ApplyDamage(Hit, Damage, nullptr, this, UDamageType::StaticClass());
		Affect(Hit);
	}
}

void ATrap::DestroyTrap()
{
	Destroy();
}

void ATrap::Affect(AActor* Hit)
{

}
