// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandArray.GetData();
}

void UMyGameInstance::Init()
{
	Super::Init();

	const int ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 index = 1; index <= ArrayNum; ++index)
	{
		Int32Array.Add(index);
	}

	Int32Array.RemoveAll(
		[](int32 val) 
		{
			return val % 2 == 0;
		}
	);

	Int32Array += {2, 4, 6, 8, 10};

	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	ensure(Int32Array == Int32ArrayCompare);

	int32 Sum = 0;
	for (const int32 Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}

	ensure(Sum == 55);

	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum == SumByAlgo);
	
	TSet<int32> Int32Set;
	for (int32 index = 1; index <= ArrayNum; ++index)
	{
		Int32Set.Add(index);
	}

	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	const int32 StudentNum = 300;
	for (int Index = 0; Index < StudentNum; ++Index)
	{
		StudentsData.Emplace(FStudentData(MakeRandomName(), Index));
	}

	TArray<FString> AllStudentName;
	Algo::Transform(StudentsData, AllStudentName,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수 : %d"), AllStudentName.Num());

	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentsData, AllUniqueNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수 : %d"), AllUniqueNames.Num());

	Algo::Transform(StudentsData, StudentsMap,
		[](const FStudentData& Val)
		{
			return TPair<int32, FString>(Val.Order, Val.Name);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수 : %d"), StudentsMap.Num());

	TMap<FString, int32> StudentsMapByUniqueName;
	Algo::Transform(StudentsData, StudentsMapByUniqueName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수 : %d"), StudentsMapByUniqueName.Num());

	TMultiMap<FString, int32> StudentsMapByName;
	Algo::Transform(StudentsData, StudentsMapByName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티맵의 레코드 수 : %d"), StudentsMapByName.Num());

	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수 : %d"), *TargetName, AllOrders.Num());

	TSet<FStudentData> StudentsSet;
	for (int Index = 0; Index < StudentNum; ++Index)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), Index));
	}
}
