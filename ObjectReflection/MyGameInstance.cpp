// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UMyGameInstance::StaticClass();

	//check(ClassRuntime == ClassCompile);
	//check(ClassRuntime != ClassCompile);
	//ensure(ClassRuntime != ClassCompile);
	//ensureMsgf(ClassRuntime != ClassCompile, TEXT("에러 발생"));

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s"), *ClassRuntime->GetName());

	SchoolName = TEXT("대학교");
	UE_LOG(LogTemp, Log, TEXT("학교 이름 : %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("기본값 학교 이름 : %s"), *ClassRuntime->GetDefaultObject<UMyGameInstance>()->SchoolName);
}