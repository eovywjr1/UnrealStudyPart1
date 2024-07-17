// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "StudentManager.h"

void CheckUObjectIsValid(const UObject* InObject, const FString& InTag)
{
	if (InObject->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 언리얼 오브젝트"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
	if (InObject == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] nullptr 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] nullptr 아닌 언리얼 오브젝트"), *InTag);
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Emplace(NewObject<UStudent>());
	PropStudents.Emplace(NewObject<UStudent>());

	StudentManager = new FStudentManager(NewObject<UStudent>());
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	const UStudent* StudentInManager = StudentManager->GetStudent();

	delete StudentManager;
	StudentManager = nullptr;

	FString StudentInManagerTag = TEXT("StudentInManager");
	CheckUObjectIsNull(StudentInManager, StudentInManagerTag);
	CheckUObjectIsValid(StudentInManager, StudentInManagerTag);

	FString NonPropStudentTag = TEXT("NonPropStudent");
	CheckUObjectIsNull(NonPropStudent, NonPropStudentTag);
	CheckUObjectIsValid(NonPropStudent, NonPropStudentTag);

	FString PropStudentTag = TEXT("PropStudent");
	CheckUObjectIsNull(PropStudent, PropStudentTag);
	CheckUObjectIsValid(PropStudent, PropStudentTag);

	FString NonPropStudentsTag = TEXT("NonPropStudents");
	CheckUObjectIsNull(NonPropStudents[0], NonPropStudentsTag);
	CheckUObjectIsValid(NonPropStudents[0], NonPropStudentsTag);

	FString PropStudentsTag = TEXT("PropStudents");
	CheckUObjectIsNull(PropStudents[0], PropStudentsTag);
	CheckUObjectIsValid(PropStudents[0], PropStudentsTag);
}
