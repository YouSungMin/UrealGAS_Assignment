// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GameAbilitySystem/Enemy/EnemyAttributeSet.h"
#include "UI/Interface/Resource.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComp"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetDrawSize(FVector2D(300.0f, 50.0f));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); // 어빌리티 시스템 컴포넌트 초기화
	}

	FOnGameplayAttributeValueChange& onHealthChage =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetHealthAttribute());
	onHealthChage.AddUObject(this, &AEnemyCharacter::OnHealthChange);
	FOnGameplayAttributeValueChange& onMaxHealthChage =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetMaxHealthAttribute());
	onMaxHealthChage.AddUObject(this, &AEnemyCharacter::OnMaxHealthChange);

	UUserWidget* WidgetObj = HealthBarWidget->GetUserWidgetObject();
	if (WidgetObj && WidgetObj->Implements<UResource>()) // 인터페이스 구현 여부 확인
	{
		if (EnemyAttributeSet)
		{
			IResource::Execute_UpdateMax(WidgetObj, EnemyAttributeSet->GetMaxHealth());
			IResource::Execute_UpdateCurrent(WidgetObj, EnemyAttributeSet->GetHealth());
		}
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnHealthChange(const FOnAttributeChangeData& InData)
{
	if (!HealthBarWidget) return;

	UUserWidget* WidgetObj = HealthBarWidget->GetUserWidgetObject();

	if (WidgetObj && WidgetObj->Implements<UResource>())
	{
		IResource::Execute_UpdateCurrent(WidgetObj, InData.NewValue);
	}
}

void AEnemyCharacter::OnMaxHealthChange(const FOnAttributeChangeData& InData)
{
	if (!HealthBarWidget) return;

	UUserWidget* WidgetObj = HealthBarWidget->GetUserWidgetObject();

	if (WidgetObj && WidgetObj->Implements<UResource>())
	{
		IResource::Execute_UpdateMax(WidgetObj, InData.NewValue);
	}
}

