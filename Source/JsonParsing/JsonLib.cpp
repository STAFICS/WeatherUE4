#include "JsonLib.h"
#include "JsonLib1.h"
#include "JsonUtilities.h"

TArray<FCitiesId> UJsonLib::SearchCitiesData = TArray<FCitiesId>();

FString UJsonLib::JsonFullPath(FString Path)
{
	const FString JsonFilePath = FPaths::ProjectContentDir() + Path;
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);
	return JsonString;
}

void UJsonLib::LoadCitites()
{
	FString PathToFileJson = FPaths::ProjectDir() / "JsonFiles" / "city_list.json";
	FString CitiesString;

	if ((FFileHelper::LoadFileToString(CitiesString, *PathToFileJson)))
	{
		GLog->Log("Deserialize");
		FJsonObjectConverter::JsonArrayStringToUStruct<FCitiesId>(*CitiesString, &SearchCitiesData, 0, 0);
			
	}
	else
	{
		GLog->Log("Not Deserialize");
	}
}

void UJsonLib::ContainsNameCity(FString Name, TArray<FString>& CitiesName)
{
	TArray<FString> Result;
	int count = 0;
	const int MaxCount = 30;
	for (auto JsonCity : SearchCitiesData)
	{
		if (JsonCity.Name.Contains(Name) && count < MaxCount)
		{
			Result.Add(JsonCity.Name);
			count++;
		}
	}
	CitiesName = Result;
	Result.Empty();
}

void UJsonLib::GetIdByNameCity(FString NameCity, int& Id)
{
	for (auto JsonCity : SearchCitiesData)
	{
		if (JsonCity.Name.Contains(NameCity))
		{
			Id = JsonCity.Id;
		}
	}
}

void UJsonLib::httpHandler(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, 
						   bool bSucceeded, FReceivedCompleted Complete)
{
	TSharedPtr<FJsonObject> rootObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
	if (FJsonSerializer::Deserialize(jsonReader, rootObject))
	{
		TSharedPtr<FJsonObject> WeatherMain = rootObject->GetObjectField("main");

		FWeatherMain WeatherData = {
			ConvertKelvinToCelsius(WeatherMain->GetIntegerField("temp")),
			ConvertKelvinToCelsius(WeatherMain->GetIntegerField("feels_like")),
			ConvertKelvinToCelsius(WeatherMain->GetIntegerField("temp_min")),
			ConvertKelvinToCelsius(WeatherMain->GetIntegerField("temp_max")),
			WeatherMain->GetIntegerField("pressure"),
			WeatherMain->GetIntegerField("humidity"),
			rootObject->GetStringField("name"),
			rootObject->GetIntegerField("dt"),
			rootObject->GetIntegerField("id")
		};

		UJsonLib1::InsertIntoWeatherTable(WeatherData);
		UJsonLib1::InsertIntoCityTable(WeatherData.id, WeatherData.NameCity,
			WeatherData.temp, WeatherData.timestamp);

	}
	Complete.ExecuteIfBound();
}

void UJsonLib::GetWeatherById(int IdCity, FReceivedCompleted Complete)
{
	FHttpModule* http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> req = http->CreateRequest();
	FHttpRequestCompleteDelegate& delegatex = req->OnProcessRequestComplete();
	delegatex.BindStatic(&httpHandler, Complete);
	
	FString AppId = "a4e82080436c515225e4c944793ea592";
	FString URL = FString::Printf(TEXT("api.openweathermap.org/data/2.5/weather?id=%i&appid=%s"), IdCity, *AppId);

	req->SetURL(URL);
	req->SetVerb("GET");

	req->ProcessRequest();
}

int UJsonLib::ConvertKelvinToCelsius(int Kelvin)
{
	return Kelvin - 273;
}

FDateTime UJsonLib::GetDatetimeFromInt(int64 Time)
{
	return FDateTime::FromUnixTimestamp(Time);
}