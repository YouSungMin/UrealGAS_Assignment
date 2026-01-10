// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystem/Ability/GA_FireBall.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"

UGA_FireBall::UGA_FireBall()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_FireBall::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);	// 쿨타임이거나 코스트가 부족해서 실패 처리
		return;
	}

	ACharacter* AvatarCharacter = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (AvatarCharacter && ProjectileClass)
	{
		FVector MuzzleLocation = AvatarCharacter->GetActorLocation() + (AvatarCharacter->GetActorForwardVector() * 100.0f);
		FRotator MuzzleRotation = AvatarCharacter->GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = AvatarCharacter;
		SpawnParams.Instigator = AvatarCharacter;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
