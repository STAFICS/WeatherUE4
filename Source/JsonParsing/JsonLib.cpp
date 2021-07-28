// Fill out your copyright notice in the Description page of Project Settings.


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

void UJsonLib::DeserelizeJson()
{

	FString PathToFileJson = FPaths::ProjectDir() / "Content" / "JsonFiles" / "randomgenerated.json";
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

void UJsonLib::Test(FString Name, TArray<FString>& CitiesName)
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

	/*for (int i = 0; i < SearchCitiesData.Num(); i++)
	{
		if (SearchCitiesData[i].Name.Contains(Name))
		{
			Result.Add(SearchCitiesData[i].Name);
		}
	}
	CitiesName = Result;*/

}

void UJsonLib::GetIdByNameCity(FString NameCity, int& Id)
{
	int CityId;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, NameCity);
	for (auto JsonCity : SearchCitiesData)
	{
		if (JsonCity.Name.Contains(NameCity))
		{
			CityId = JsonCity.Id;
		}
	}
	Id = CityId;
}

void UJsonLib::GetWeatherById(int IdCity)
{
	FHttpModule* http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> req = http->CreateRequest();

	req->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr req, FHttpResponsePtr res, bool suc)
		{
			TSharedPtr<FJsonObject> rootObject = MakeShareable(new FJsonObject());
			TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(res->GetContentAsString());
			if (FJsonSerializer::Deserialize(jsonReader, rootObject))
			{
				TSharedPtr<FJsonObject> WeatherMain = rootObject->GetObjectField("main");

				int temp = ConvertKelvinToCelsius(WeatherMain->GetIntegerField("temp"));
				int feels_like = ConvertKelvinToCelsius(WeatherMain->GetIntegerField("feels_like"));
				int	temp_min = ConvertKelvinToCelsius(WeatherMain->GetIntegerField("temp_min"));
				int	temp_max = ConvertKelvinToCelsius(WeatherMain->GetIntegerField("temp_max"));
				int	pressure = WeatherMain->GetIntegerField("pressure");
				int	humidity = WeatherMain->GetIntegerField("humidity");
				FString NameCity = rootObject->GetStringField("name");
				int timestamp = rootObject->GetIntegerField("dt");
				int id = rootObject->GetIntegerField("id");

				FWeatherMain WeatherData = { temp, feels_like, temp_min, temp_max, pressure, humidity, NameCity, timestamp, id };

				UJsonLib1::InsertIntoWeatherTable(WeatherData);
				UJsonLib1::InsertIntoCityTable(id, NameCity, temp, timestamp);
				
				

				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(WeatherData.id));
			}
			
		});
	
	FString AppId = "a4e82080436c515225e4c944793ea592";
	FString URL = FString::Printf(TEXT("api.openweathermap.org/data/2.5/weather?id=%i&appid=%s"), IdCity, *AppId);

	req->SetURL(URL);
	req->SetVerb("GET");

	req->ProcessRequest();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "OK");
}

int UJsonLib::ConvertKelvinToCelsius(int Kelvin)
{

	return Kelvin - 273;

}

FDateTime UJsonLib::GetDatetimeFromInt(int64 Time)
{
	return FDateTime::FromUnixTimestamp(Time);
}