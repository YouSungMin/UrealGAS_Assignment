// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_FireBall.generated.h"

/**
 * 
 */
UCLASS()
class UREALGAS_ASSIGNMENT_API UGA_FireBall : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_FireBall();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AActor> ProjectileClass;
};
