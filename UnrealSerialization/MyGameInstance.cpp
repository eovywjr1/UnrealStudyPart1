// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"

void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] 이름 %s 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

UMyGameInstance::UMyGameInstance()
{}

void UMyGameInstance::Init()
{
	Super::Init();

	FStudnetData RawDataSrc(16, TEXT("이득우"));

	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더 : %s"), *SavedDir);

	const FString RawDataFileName(TEXT("RawData.bin"));
	FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로 : %s"), *RawDataAbsolutePath);

	FPaths::MakeStandardFilename(RawDataAbsolutePath);
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로 : %s"), *RawDataAbsolutePath);

	FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
	if (RawFileWriterAr)
	{
		*RawFileWriterAr << RawDataSrc;

		RawFileWriterAr->Close();
		delete RawFileWriterAr;
		RawFileWriterAr = nullptr;
	}

	FStudnetData RawDataDest;
	FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
	if (RawFileReaderAr)
	{
		*RawFileReaderAr << RawDataDest;

		RawFileReaderAr->Close();
		delete RawFileReaderAr;
		RawFileReaderAr = nullptr;

		UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %d 순번 %s"), RawDataDest.Order, *RawDataDest.Name);
	}

	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetOrder(59);
	StudentSrc->SetName(TEXT("이득우"));

	const FString ObjectDataFileName(TEXT("ObjectData.bin"));
	FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
	FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

	TArray<uint8> BufferArray;
	FMemoryWriter MemoryWriterAr(BufferArray);
	StudentSrc->Serialize(MemoryWriterAr);

	TUniquePtr<FArchive> FileWriteAr(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath));
	if (FileWriteAr)
	{
		*FileWriteAr << BufferArray;
		FileWriteAr->Close();
	}

	TArray<uint8> BufferArrayFromFile;
	TUniquePtr<FArchive> FileReaderAr(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath));
	if (FileReaderAr)
	{
		*FileReaderAr << BufferArrayFromFile;
		FileReaderAr->Close();
	}

	FMemoryReader MemoryReaderAr(BufferArrayFromFile);
	TObjectPtr<UStudent> StudentDest(NewObject<UStudent>());
	StudentDest->Serialize(MemoryReaderAr);

	PrintStudentInfo(StudentDest.Get(), TEXT("ObjectData"));

	const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
	FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
	FPaths::MakeStandardFilename(JsonDataAbsolutePath);

	TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>();
	FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc);

	FString JsonOutString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
	if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
	{
		FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath);

		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);
		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString); // 문자열이 이상한 값이 들어오면 안 만들어지면 null이기 때문에 포인터로

		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			TObjectPtr<UStudent> JsonStudentDest(NewObject<UStudent>());
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest.Get()))
			{
				PrintStudentInfo(JsonStudentDest.Get(), TEXT("JsonData"));
			}
		}
	}
}
