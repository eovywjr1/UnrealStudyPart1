// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

class UStudent;

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("홍길동");
		Order = -1;
	}

	FStudentData(const FString& InName, const int32 InOrder) : Name(InName), Order(InOrder) {}

	bool operator== (const FStudentData& InStudentData) const
	{
		return Order == InStudentData.Order;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	FString Name;
	int32 Order;
};

UCLASS()
class UNREALCONTAINER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

private:
	TArray<FStudentData> StudentsData;

	UPROPERTY()
	TArray<TObjectPtr<UStudent>> Students;

	TMap<int32, FString> StudentsMap;
};
