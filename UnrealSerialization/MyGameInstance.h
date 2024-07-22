// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

class UStudent;

struct FStudnetData
{
	FStudnetData() = default;
	FStudnetData(const int32 InOrder, const FString& InName) : Order(InOrder), Name(InName) {}

	friend FArchive& operator<< (FArchive& Ar, FStudnetData& InStudnetData)
	{
		Ar << InStudnetData.Order;
		Ar << InStudnetData.Name;

		return Ar;
	}

	int32 Order = -1;
	FString Name = TEXT("홍길동");
};

UCLASS()
class UNREALSERIALIZATION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override final;

private:
	void SaveStudentPackage() const;
	void LoadStudentPackage() const;
	void LoadStudentObject() const;

	UPROPERTY()
	TObjectPtr<UStudent> StudentSrc;

	static const FString PackageName;
	static const FString AssetName;
	
	FStreamableManager StreamableManager;
	TSharedPtr<FStreamableHandle> StreamableHandle;
};
