// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

class UStudent;
class FStudentManager;

UCLASS()
class UNREALMEMORY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

private:
	TObjectPtr<UStudent> NonPropStudent;
	
	UPROPERTY()
	TObjectPtr<UStudent> PropStudent;

	TArray<TObjectPtr<UStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<UStudent>> PropStudents;

	FStudentManager* StudentManager = nullptr;
};
