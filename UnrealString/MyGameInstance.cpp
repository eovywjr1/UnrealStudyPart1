// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	TCHAR LogCharArray[] = TEXT("Hello-Unreal");
	UE_LOG(LogTemp, Log, LogCharArray);

	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%S"), *LogCharString);	// 세 번째 파라미터에는 배열이기 때문에 %s로 배열을 전달
														// %s에 대응될 때는 TCHAR의 포인터를 전달해야 하는데, FString에 포인터 연산자 사용
}
