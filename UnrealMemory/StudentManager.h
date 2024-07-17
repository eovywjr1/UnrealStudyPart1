// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class UStudent;

class UNREALMEMORY_API FStudentManager : FGCObject
{
public:
	FStudentManager(UStudent* InStudent) : SafeStudent(InStudent) {}

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}

	const UStudent* GetStudent() const { return SafeStudent; }

private:
	UStudent* SafeStudent = nullptr;
};
