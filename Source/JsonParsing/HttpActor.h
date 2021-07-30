// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HttpActor.generated.h"

UCLASS()
class JSONPARSING_API AHttpActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHttpActor();

	FHttpModule* Http;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void fMyHttpCall();

	void fOnHttpRecerve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};
