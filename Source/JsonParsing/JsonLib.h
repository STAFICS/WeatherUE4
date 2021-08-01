
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonStruct.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "JsonLib.generated.h"

DECLARE_DYNAMIC_DELEGATE(FReceivedCompleted);

UCLASS()
class JSONPARSING_API UJsonLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	static TArray<FCitiesId> SearchCitiesData;

	static FString JsonFullPath(FString Path);

	static FHttpModule* Http;

	UFUNCTION(BlueprintCallable)
	static void LoadCitites();

	UFUNCTION(BlueprintCallable)
	static void ContainsNameCity(FString Name, TArray<FString>& CitiesName);

	UFUNCTION(BlueprintCallable)
	static void GetIdByNameCity(FString NameCity, int& Id);

	static void httpHandler(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FReceivedCompleted Complete);

	UFUNCTION(BlueprintCallable)
	static void GetWeatherById(int IdCity, FReceivedCompleted Complete);

	UFUNCTION(BlueprintCallable)
	static int ConvertKelvinToCelsius(int Kelvin);

	UFUNCTION(BlueprintCallable)
	static FDateTime GetDatetimeFromInt(int64 Time);

};
