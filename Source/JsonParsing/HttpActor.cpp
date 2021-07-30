// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpActor.h"

// Sets default values
AHttpActor::AHttpActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Http = &FHttpModule::Get();

}

// Called when the game starts or when spawned
void AHttpActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHttpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHttpActor::fMyHttpCall()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	//TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::fOnHttpRecerve);

	Request->SetURL("api.openweathermap.org/data/2.5/weather?id=1486209&appid=a4e82080436c515225e4c944793ea592");// Êóäà îòïðàâëÿòü çàïðîñ
	Request->SetVerb("GET");

	Request->ProcessRequest();
}

void AHttpActor::fOnHttpRecerve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Response->GetContentAsString());
}