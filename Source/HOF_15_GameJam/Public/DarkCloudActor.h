// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DarkCloudActor.generated.h"




UCLASS()
class HOF_15_GAMEJAM_API ADarkCloudActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADarkCloudActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	float cloudSpeed;
	ACharacter* playerCharacter;
};
