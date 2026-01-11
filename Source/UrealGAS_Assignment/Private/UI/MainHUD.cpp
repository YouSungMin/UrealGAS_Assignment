// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "UI/MainHUDWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainHUDWidget)
	{
		MainHUDWidgetInstance = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDWidget);

		if (MainHUDWidgetInstance)
		{
			MainHUDWidgetInstance->AddToViewport();
		}
	}
}
