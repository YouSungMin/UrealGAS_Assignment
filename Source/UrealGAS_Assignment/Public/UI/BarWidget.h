// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/Resource.h"
#include "BarWidget.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;

UCLASS()
class UREALGAS_ASSIGNMENT_API UBarWidget : public UUserWidget, public IResource
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetProgressColor(FLinearColor InColor);

	virtual void UpdateCurrent_Implementation(float Invalue)override;
	virtual void UpdateMax_Implementation(float Invalue)override;
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> BackgroundProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Current;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Max;

private:
	float CurrentValue = 0.0f;
	float MaxValue = 1.0f;
};
