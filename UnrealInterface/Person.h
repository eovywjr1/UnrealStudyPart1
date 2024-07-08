// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UNREALINTERFACE_API UPerson : public UObject
{
	GENERATED_BODY()
	
public:
	UPerson();

	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void Setname(const FString& InName) { Name = InName; }

protected:
	UPROPERTY()
	FString Name;
};
