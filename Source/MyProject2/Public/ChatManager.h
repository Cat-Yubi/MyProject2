// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChatManager.generated.h"

class UChatCommunicator;

UCLASS()
class MYPROJECT2_API AChatManager : public AActor
{
	GENERATED_BODY()

public:
	AChatManager();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable)
	void ServerSendMessage(int32 UniqueId, const FText& ChatText);
	
	UFUNCTION(Server, Reliable)
	void ServerAddCommunicator(UChatCommunicator* Communicator);
	
private:
	TArray<UChatCommunicator*> Communicators;
	FString RandomString;
};
