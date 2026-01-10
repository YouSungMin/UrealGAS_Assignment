// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameAbilitySystem/Player/PlayerAttributeSet.h"
#include "EnhancedInputComponent.h"
#include "GameAbilitySystem/Ability/GameAbilityEnums.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); // 어빌리티 시스템 컴포넌트 초기화

		if (FireBallClass)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(
					FireBallClass,											// 어빌리티 클래스
					1,														// 레벨
					static_cast<int32>(EAbilityInputID::FireBall),			// 입력 ID
					this													// Source
				)
			);
		}
	}

	FOnGameplayAttributeValueChange& onManaChage =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute());
	onManaChage.AddUObject(this, &APlayerCharacter::OnManaChange);

	FOnGameplayAttributeValueChange& onMaxManaChage =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute());
	onMaxManaChage.AddUObject(this, &APlayerCharacter::OnMaxManaChange);

	if (PlayerAttributeSet)
	{
		
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInput)
	{
		EnhancedInput->BindAction(IA_FireBall, ETriggerEvent::Started, this, &APlayerCharacter::OnFireBall);
	}
}

void APlayerCharacter::OnManaChange(const FOnAttributeChangeData& InData)
{
}

void APlayerCharacter::OnMaxManaChange(const FOnAttributeChangeData& InData)
{
}

void APlayerCharacter::OnFireBall()
{
	UE_LOG(LogTemp, Log, TEXT("OnFireBall"));

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::FireBall));
	}
}

