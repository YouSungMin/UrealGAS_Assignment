// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GCNA_Burn.generated.h"

/**
 * 
 */
UCLASS()
class UREALGAS_ASSIGNMENT_API AGCNA_Burn : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
public:
	AGCNA_Burn();
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TObjectPtr<class UNiagaraSystem> BurnVFX = nullptr;
private:
	UPROPERTY()
	TWeakObjectPtr<class UNiagaraComponent> SpawnedVFX = nullptr;
};
