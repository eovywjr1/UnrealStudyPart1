// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("이학생");
	Card->SetCardType(ECardType::Student);
}

void UStudent::DoLesson() const
{
	ILessonInterface::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%s님이 공부합니다."), *Name);
}

void UStudent::GetNotification(const FString& InSchoolName, const FString& InNewContents)
{
	UE_LOG(LogTemp, Log, TEXT("[Student] %s님이 %s로부터 받은 메시지 : %s"), *Name, *InSchoolName, *InNewContents);
}
