#include "MineItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

AMineItem::AMineItem()
{
	ExplosionDamage = 20.f;
	ExplosionRange = 500.f;
	ExplosionDelay = 3.f;

	ItemType = "Mine";

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRange);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(RootComponent);
}

void AMineItem::ActivateItem(AActor* Activator)
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explode, ExplosionDelay, false);
}

void AMineItem::Explode()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("Mine exploded"));
	}
	TArray<AActor*> OverlappedActors;
	ExplosionCollision->GetOverlappingActors(OverlappedActors);
	for (AActor* Actor : OverlappedActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(Actor, ExplosionDamage, nullptr, this, UDamageType::StaticClass());
		}
	}
}
