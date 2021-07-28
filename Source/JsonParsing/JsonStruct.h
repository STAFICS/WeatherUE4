// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JsonStruct.generated.h"

USTRUCT(BlueprintType)
struct FWeatherCityCoord
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float Longitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float Latitude;
};

USTRUCT(BlueprintType)
struct FCitiesId
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	FString Country;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	FWeatherCityCoord CityCoord;

	FCitiesId() :
		Id(0), Name(""), Country(""), CityCoord(FWeatherCityCoord())
	{
	}
};

USTRUCT(BlueprintType)
struct FWeatherMain
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int temp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int feels_like;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int temp_min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int temp_max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int pressure;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int humidity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	FString NameCity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int timestamp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int id;

};

USTRUCT(BlueprintType)
struct FWeatherMini
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	FString NameCity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int temp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	int timestemp;

};

