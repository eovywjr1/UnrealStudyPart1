// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

const FString UMyGameInstance::PackageName = TEXT("/Game/Student");
const FString UMyGameInstance::AssetName = TEXT("TopStudent");

void PrintStudentInfo(const UStudent* InStudent, const FString& InTag)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] 이름 %s 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

UMyGameInstance::UMyGameInstance()
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 생성자에서 에셋 로딩할 때는 ConstructorHelpers::FObjectFinder<>() 사용
	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_TopStudent(*TopSoftObjectPath);
	if (UASSET_TopStudent.Succeeded())
	{
		PrintStudentInfo(UASSET_TopStudent.Object, TEXT("Constructor"));
	}
}

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

	SaveStudentPackage();
	//LoadStudentPackage();
	//LoadStudentObject();

	// 에셋 비동기 로드
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	StreamableHandle = StreamableManager.RequestAsyncLoad(TopSoftObjectPath,
		[&]()
		{
			if (StreamableHandle.IsValid() && StreamableHandle->HasLoadCompleted())
			{
				UStudent* TopStudent = Cast<UStudent>(StreamableHandle->GetLoadedAsset());
				if (TopStudent)
				{
					PrintStudentInfo(TopStudent, TEXT("AsyncLoad"));

					StreamableHandle->ReleaseHandle();
					StreamableHandle.Reset();
				}
			}
		}
	);
}

void UMyGameInstance::SaveStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}
	else
	{
		StudentPackage = CreatePackage(*PackageName);
	}

	EObjectFlags ObjectFlag = RF_Public | RF_Standalone;

	TObjectPtr<UStudent> TopStudent = NewObject<UStudent>(StudentPackage, UStudent::StaticClass(), *AssetName, ObjectFlag);
	TopStudent->SetName(TEXT("이득우"));
	TopStudent->SetOrder(36);

	const uint8 NumOfSubSize = 10;
	for (uint8 Index = 1; Index <= NumOfSubSize; ++Index)
	{
		FString SubObjectName = FString::Printf(TEXT("Stduent%d"), Index);
		TObjectPtr<UStudent> SubStudent = NewObject<UStudent>(TopStudent, UStudent::StaticClass(), *SubObjectName, ObjectFlag);
		SubStudent->SetName(FString::Printf(TEXT("학생%d"), Index));
		SubStudent->SetOrder(Index);
	}

	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지 저장"));
	}
}

void UMyGameInstance::LoadStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("패키지 없음"));
	}

	StudentPackage->FullyLoad();

	UStudent* TopStudent = FindObject<UStudent>(StudentPackage, *AssetName);
	PrintStudentInfo(TopStudent, TEXT("FindObject Asset"));
}

void UMyGameInstance::LoadStudentObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	// 패키지를 로딩하지 않기 때문에 첫 번째 인자를 nullptr로
	UStudent* TopStudent = LoadObject<UStudent>(nullptr, *TopSoftObjectPath);
	PrintStudentInfo(TopStudent, TEXT("LoadObject Asset"));
}
