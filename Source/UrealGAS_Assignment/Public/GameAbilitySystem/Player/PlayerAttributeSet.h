// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameAbilitySystem/GASMacros.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UREALGAS_ASSIGNMENT_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPlayerAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MagicPower;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MagicPower);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxMana);
};
