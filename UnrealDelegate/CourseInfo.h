// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSiganture, const FString&, const FString&);

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

	FCourseInfoOnChangedSiganture OnChanged;

private:
	FString Contents;
};
