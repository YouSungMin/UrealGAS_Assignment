// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/GEEC/GEEC_FireBallDamage.h"
#include "GameAbilitySystem/Player/PlayerAttributeSet.h"
#include "GameAbilitySystem/Enemy/EnemyAttributeSet.h"

// UGEEC_FireDamage 계산에 필요한 어트리뷰트를 캡처하기 위한 구조체(이 계산이 어디에 영향을 줄것인가)
struct FFireDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);	// Health 어트리뷰트를 캡처할 것이라고 정의
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPower);

	FFireDamageStatics()
	{
		// UStatusAttributeSet의 Health를 캡처하는데, Targer으로 부터 캡처, 스냅샷은 사용하지 않음
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, Health, Target, false);

		// UStatusAttributeSet의 AttackPower를 캡처하는데, Source으로 부터 캡처, 공격 시점의 값 가져오기
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, MagicPower, Source, true);
	}
};

static FFireDamageStatics& FireDamageStatics()
{
	static FFireDamageStatics Statics;
	return Statics;
}

UGEEC_FireBallDamage::UGEEC_FireBallDamage()
{
	RelevantAttributesToCapture.Add(FireDamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(FireDamageStatics().MagicPowerDef);

	Tag_DeBuffBurn = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burn"));
	Tag_ElementFire = FGameplayTag::RequestGameplayTag(FName("Element.Fire"));
}

void UGEEC_FireBallDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (TargetASC && SourceASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

		const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();	// 소스의 태그 가져오기
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();	// 타겟의 태그 가져오기

		float Damage = MinimumDamage;

		FAggregatorEvaluateParameters EvaluateParameters;
		EvaluateParameters.SourceTags = SourceTags;
		EvaluateParameters.TargetTags = TargetTags;
		float AttackPower = 0.0f;
		bool Result = ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			FireDamageStatics().MagicPowerDef,
			EvaluateParameters,
			AttackPower);

		if (Result)
		{
			Damage += AttackPower;
			UE_LOG(LogTemp, Log, TEXT("%f"), Damage);
		}


		if (SourceTags && SourceTags->HasTag(Tag_ElementFire)		// 공격 데미지가 불속성이고
			&& TargetTags && TargetTags->HasTag(Tag_DeBuffBurn))	// 피격자가 화상 디버프를 가지고있으면
		{
			Damage *= DamageMultiplier; // 데미지 두배
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					FireDamageStatics().HealthProperty,	// Health 어트리뷰트를 변경
					EGameplayModOp::Additive,			// 더해줌
					-Damage								// -Damage 만큼 처리
				)
			);
		}
	}
}
