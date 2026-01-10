// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "AbilitySystemInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UREALGAS_ASSIGNMENT_API APlayerCharacter : public ACharacter//, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//void OnManaChange(const FOnAttributeChangeData& InData);
	//void OnMaxManaChange(const FOnAttributeChangeData& InData);

};
