// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"

void UMyGameInstance::Init()
{
	Super::Init();

	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };

	for (const UPerson* Person : Persons)
	{
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);

		const ECardType OwnCardType = OwnCard->GetCardType();
		//UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 : %d"), *Person->GetName(), OwnCardType);

		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UnrealComposition.ECardType"));
		if (CardEnumType) 
		{
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)OwnCardType).ToString();
			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류 : %s"), *Person->GetName(), *CardMetaData);
		}
	}
}
