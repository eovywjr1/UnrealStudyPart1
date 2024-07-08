// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

void UMyGameInstance::Init()
{
	Super::Init();

	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };

	for (const UPerson* Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름 : %s"), *Person->GetName());
	}

	for (const UPerson* Person : Persons)
	{
		const ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 있습니다."), *Person->GetName());
			LessonInterface->DoLesson();
		}
		else 
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할 수 없습니다."), *Person->GetName());
		}
	}
}
