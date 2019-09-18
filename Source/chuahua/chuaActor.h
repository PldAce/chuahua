// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "chuaActor.generated.h"

UCLASS()
class CHUAHUA_API AchuaActor : public AActor
{
	GENERATED_BODY()
	
public:
	FHttpModule* Http;

	/* The actual HTTP call */
	UFUNCTION()
		void MyHttpCall();

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Sets default values for this actor's properties
	AchuaActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};