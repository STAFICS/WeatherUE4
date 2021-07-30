// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JsonStruct.h"
#include "JsonParser.generated.h"

UCLASS()
class JSONPARSING_API AJsonParser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJsonParser();

	//static TArray<FSearchCity> SearchCitiesData;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//static TArray<FSearchCity> SearchCitiesData;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void fGetArrCitiesName(TArray<FString>& ListCitiesName);

};
