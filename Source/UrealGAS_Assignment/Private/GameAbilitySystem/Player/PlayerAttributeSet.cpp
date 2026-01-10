// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Player/PlayerAttributeSet.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitMana(100.0f);
	InitMaxMana(100.0f);
	InitMagicPower(10.0f);
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
