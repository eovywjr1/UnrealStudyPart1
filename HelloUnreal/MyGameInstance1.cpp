// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance1.h"

void UMyGameInstance1::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal!"));
}
