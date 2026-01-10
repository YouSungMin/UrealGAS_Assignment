// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BarWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


void UBarWidget::SetProgressColor(FLinearColor InColor)
{
	BackgroundProgressBar->SetFillColorAndOpacity(InColor);
}

void UBarWidget::UpdateCurrent_Implementation(float Invalue)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(Invalue)));
	CurrentValue = Invalue;
	BackgroundProgressBar->SetPercent(Invalue / MaxValue);
}

void UBarWidget::UpdateMax_Implementation(float Invalue)
{
	Max->SetText(FText::AsNumber(FMath::RoundToInt(Invalue)));
	MaxValue = Invalue;
	BackgroundProgressBar->SetPercent(CurrentValue / MaxValue);
}
