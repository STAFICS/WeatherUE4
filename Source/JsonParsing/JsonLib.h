
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonStruct.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "JsonLib.generated.h"

UCLASS()
class JSONPARSING_API UJsonLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	static TArray<FCitiesId> SearchCitiesData;

	static FString JsonFullPath(FString Path);

	static FHttpModule* Http;

	UFUNCTION(BlueprintCallable)
	static void DeserelizeJson();

	UFUNCTION(BlueprintCallable)
	static void Test(FString Name, TArray<FString>& CitiesName);

	UFUNCTION(BlueprintCallable)
	static void GetIdByNameCity(FString NameCity, int& Id);

	UFUNCTION(BlueprintCallable)
	static void GetWeatherById(int IdCity);

	UFUNCTION(BlueprintCallable)
	static int ConvertKelvinToCelsius(int Kelvin);

	UFUNCTION(BlueprintCallable)
	static FDateTime GetDatetimeFromInt(int64 Time);

};
