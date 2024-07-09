// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */

class UCard;

UCLASS()
class UNREALCOMPOSITION_API UPerson : public UObject
{
	GENERATED_BODY()
	
public:
	UPerson();

	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }

	FORCEINLINE const UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(UCard* InCard) { Card = InCard; }

protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	TObjectPtr<UCard> Card;
};
