// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Enemy/EnemyAttributeSet.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())	// 이 함수가 Health 어트리뷰트가 변경되어서 호출되었는지 확인
	{

		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
		UE_LOG(LogTemp, Log, TEXT("Health가 변경 (%.1f -> %.1f)"), GetHealth(), NewValue);
	}
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
