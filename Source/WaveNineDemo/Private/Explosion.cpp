#include "Explosion.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AExplosion::AExplosion()
{
    TriggerDelay = 2.f;
    AffectRadius = 200.f;
    Damage = 30.f;   
}

void AExplosion::TriggerTrap()
{
    Super::TriggerTrap();

    StaticMesh->SetVisibility(false);

	UParticleSystemComponent* Particle = nullptr;
	if (PickupParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PickupParticle,
			GetActorLocation(),
			GetActorRotation(),
			true
		);
	}

	TWeakObjectPtr WeakParticle = Particle;
	if (Particle)
	{
		GetWorldTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			[WeakParticle]()
			{
				if (UParticleSystemComponent* PSC = WeakParticle.Get())
					PSC->DestroyComponent();
			},
			2.f,
			false
		);
	}
}
