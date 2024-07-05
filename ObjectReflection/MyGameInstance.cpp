// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"

void UMyGameInstance::Init()
{
	Super::Init();

	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 : %s"), *Student->GetName());

	FString CurrentTeacherName;
	FString NewTeacherName(TEXT("이득우"));
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp) 
	{
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 : %s"), *CurrentTeacherName);

		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름 : %s"), *Teacher->GetName());
	}

	Student->DoLesson();
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if(DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}
}
