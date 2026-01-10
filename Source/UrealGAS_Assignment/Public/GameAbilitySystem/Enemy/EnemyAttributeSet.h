// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameAbilitySystem/GASMacros.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UREALGAS_ASSIGNMENT_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UEnemyAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;
public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHealth);
};
