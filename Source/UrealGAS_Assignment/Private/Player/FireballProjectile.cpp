// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FireballProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AFireballProjectile::AFireballProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic")); 
	SphereComponent->InitSphereRadius(200.0f);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(SphereComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComponent->InitialSpeed = 1000.0f;
	MovementComponent->MaxSpeed = 1000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AFireballProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFireballProjectile::OnSphereOverlap);
}

void AFireballProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || OtherActor == GetInstigator()) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (TargetASC)
	{
		if (BurnEffectClass)
		{
			FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
			ContextHandle.AddSourceObject(this);

			// Àû¿ë
			TargetASC->ApplyGameplayEffectToSelf(BurnEffectClass.GetDefaultObject(), 1.0f, ContextHandle);
			UE_LOG(LogTemp, Log, TEXT("Burn"));
		}

		if (DamageEffectClass)
		{
			FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
			ContextHandle.AddSourceObject(this);
			TargetASC->ApplyGameplayEffectToSelf(DamageEffectClass.GetDefaultObject(), 1.0f, ContextHandle);
		}
	}
	Destroy();
}

