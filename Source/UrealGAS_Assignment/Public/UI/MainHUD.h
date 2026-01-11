// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UMainHUDWidget;
/**
 * 
 */
UCLASS()
class UREALGAS_ASSIGNMENT_API AMainHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UMainHUDWidget* GetMainHUDWidget() const { return MainHUDWidgetInstance; }
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainHUDWidget> MainHUDWidget;

private:
	UPROPERTY()
	TObjectPtr<UMainHUDWidget> MainHUDWidgetInstance;
};
