// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

class UBarWidget;
/**
 * 
 */
UCLASS()
class UREALGAS_ASSIGNMENT_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite ,meta = (BindWidget))
	TObjectPtr<UBarWidget> ManaBar;
};
