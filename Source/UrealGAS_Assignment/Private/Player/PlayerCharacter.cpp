// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "GameAbilitySystem/Player/PlayerAttributeSet.h"
#include "GameAbilitySystem/Ability/GameAbilityEnums.h"
#include "UI/MainHUD.h"
#include "UI/MainHUDWidget.h"
#include "UI/BarWidget.h"
#include "UI/Interface/Resource.h"

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
		InitializeHUD();
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

void APlayerCharacter::InitializeHUD()
{
	if (!PlayerAttributeSet) return;

	if (UBarWidget* ManaBar = GetManaBarWidget())
	{
		if (ManaBar->Implements<UResource>())
		{
			IResource::Execute_UpdateMax(ManaBar, PlayerAttributeSet->GetMaxMana());
			IResource::Execute_UpdateCurrent(ManaBar, PlayerAttributeSet->GetMana());
		}
	}
}

void APlayerCharacter::OnManaChange(const FOnAttributeChangeData& InData)
{
	if (UBarWidget* ManaBar = GetManaBarWidget())
	{
		if (ManaBar->Implements<UResource>())
		{
			IResource::Execute_UpdateCurrent(ManaBar, InData.NewValue);
		}
	}
}

void APlayerCharacter::OnMaxManaChange(const FOnAttributeChangeData& InData)
{
	if (UBarWidget* ManaBar = GetManaBarWidget())
	{
		if (ManaBar->Implements<UResource>())
		{
			IResource::Execute_UpdateMax(ManaBar, InData.NewValue);
		}
	}
}

void APlayerCharacter::OnFireBall()
{
	UE_LOG(LogTemp, Log, TEXT("OnFireBall"));

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::FireBall));
	}
}

UBarWidget* APlayerCharacter::GetManaBarWidget() const
{
	// 컨트롤러 확인
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// HUD 확인
		if (AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD()))
		{
			// MainWidget 확인
			if (UMainHUDWidget* MainWidget = HUD->GetMainHUDWidget())
			{
				// ManaBar 반환
				return MainWidget->ManaBar;
			}
		}
	}
	return nullptr;
}

