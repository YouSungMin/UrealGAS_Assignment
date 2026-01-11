// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_FireBallDamage.generated.h"

/**
 * 
 */
UCLASS()
class UREALGAS_ASSIGNMENT_API UGEEC_FireBallDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGEEC_FireBallDamage();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	float MinimumDamage = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	float DamageMultiplier = 2.0f;

private:
	FGameplayTag Tag_DeBuffBurn;
	FGameplayTag Tag_ElementFire;
};
