// Fill out your copyright notice in the Description page of Project Settings.

#include "chuahua.h"
#include "chuaActor.h"
#include "Engine.h"

// Sets default values
AchuaActor::AchuaActor()
{
	//When the object is constructed, Get the HTTP module
	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AchuaActor::BeginPlay()
{
	MyHttpCall();
	Super::BeginPlay();
}

/*Http call*/
void AchuaActor::MyHttpCall()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AchuaActor::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("134.209.168.48");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void AchuaActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		int32 recievedInt = JsonObject->GetIntegerField("customInt");

		//Output it to the engine
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	}
}

