#include "BaseItem.h"
#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(Scene);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);

	RotationSpeed = 90.f;
	MaxRange = 50.f;
	Period = 3.f;
	PhaseOffset = 0.f;
	RotationOffset = 0.f;
	RunningTime = 0.f;
}

void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(FName("Player")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Overlap")));
		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseItem::ActivateItem(AActor* Activator)
{
}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	Destroy();
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	const float SafeRange = FMath::Max(MaxRange, 1.f);
	EndLocation = StartLocation + FVector(0.f, 0.f, SafeRange);

	RunningTime = FMath::Max(PhaseOffset * Period, 0.f);
	StaticMesh->SetRelativeRotation(FRotator(0.f, RotationOffset, 0.f));
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	Rotate(DeltaTime);
}

void ABaseItem::Move(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("ABaseItem::Move")));
	const float SafePeriod = FMath::Max(Period, KINDA_SMALL_NUMBER);
	RunningTime = FMath::Fmod(RunningTime + DeltaTime, SafePeriod);

	const float Alpha = RunningTime / (SafePeriod * 0.5f);
	const float T = (1 - FMath::Cos(Alpha * PI)) * 0.5f;

	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, T));
}

void ABaseItem::Rotate(float DeltaTime)
{
	StaticMesh->AddRelativeRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}
