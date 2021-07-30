// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonParser.h"
#include "JsonUtilities.h"

//TArray<FSearchCity> AJsonParser::SearchCitiesData = TArray<FSearchCity>();

// Sets default values
AJsonParser::AJsonParser()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJsonParser::BeginPlay()
{

	Super::BeginPlay();



	//const FString JsonFilePath = FPaths::ProjectContentDir() + "/JsonFiles/randomgenerated.json";
	//FString JsonString; //Json converted to FString

	//FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

	////Displaying the json in a string format inside the output log
	//GLog->Log("Json String:");
	////GLog->Log(JsonString);

	////Create a json object to store the information from the json string
	////The json reader is used to deserialize the json object later on
	//TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	//TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	//if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	//{
	//	GLog->Log("Deserialize");
	//	//FJsonObjectConverter::JsonArrayStringToUStruct<FSearchCity>(*JsonString, &SearchCitiesData, 0, 0);
	//	TArray<TSharedPtr<FJsonValue>> arr = JsonObject->GetArrayField("CitiesList");
	//	<TSharedPtr<FJsonValue>>


	//}
	//else
	//{
	//	GLog->Log("couldn't deserialize");
	//}

}

// Called every frame
void AJsonParser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJsonParser::fGetArrCitiesName(TArray<FString>& ListCitiesName)
{

	const FString JsonFilePath = FPaths::ProjectContentDir() + "/JsonFiles/randomgenerated.json";
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<FCitiesId> CitiesId;
	//TArray<FString> ListCitiesName;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}

		TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("CitiesList"));
		

		for (int i = 0; i < objArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> value = objArray[i];
			TSharedPtr<FJsonObject> json = value->AsObject();
			FString jsonName = json->GetStringField("name");
			ListCitiesName.Add(jsonName);

			GLog->Log(jsonName);
		}

		
		
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}
}