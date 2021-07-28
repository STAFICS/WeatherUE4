// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonStruct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonLib1.generated.h"

/**
 * 
 */
UCLASS()
class JSONPARSING_API UJsonLib1 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void DatabaseOpen();

	UFUNCTION(BlueprintCallable)
	static void CreateTableWeather();

	UFUNCTION(BlueprintCallable)
	static void CreateTableCities();

	UFUNCTION(BlueprintCallable)
	static void InsertIntoWeatherTable(FWeatherMain WeatherData);

	UFUNCTION(BlueprintCallable)
	static void InsertIntoCityTable(int IdCity, FString NameCity, int temp, int timestamp);

	UFUNCTION(BlueprintCallable)
	static void DeleteCityFromCitiesTable(int id);

	UFUNCTION(BlueprintCallable)
	static void DeleteWeathrsFromWeatherTable(int id);

	UFUNCTION(BlueprintCallable)
	static void GetSavedCitys(TArray<FWeatherMini>& SavedCitys);

	UFUNCTION(BlueprintCallable)
	static void GetHistoryBySelectCity(int SelectedCityId, TArray<FWeatherMain>& History);

	UFUNCTION(BlueprintCallable)
	static void DatabaseClose();

	static FString GetPathDB();
	
};
