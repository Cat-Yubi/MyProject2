// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChatCommunicator.generated.h"

class AChatManager;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT2_API UChatCommunicator : public UActorComponent
{
	GENERATED_BODY()

public:
	UChatCommunicator();

protected:
	virtual void BeginPlay() override;

public:
	void RequestSendMessage(const FText& ChatText);

	UFUNCTION(Client, Reliable)
	void ClientResultId(int32 ClientId);

	UFUNCTION(Client, Reliable)
	void ClientNotice(const FString& Message);
	
private:
	UFUNCTION(Server, Reliable)
	void ServerSendMessage(int32 SendId, const FText& ChatText);

	UFUNCTION(Server, Reliable)
	void ServerSetCommunicator(UChatCommunicator* Communicator);

	UFUNCTION()
	void OnReceiveChatManager(AChatManager* Manager);

	void ScreenDebugMessage(const FString& Message);

	UPROPERTY()
	AChatManager* ChatManagerInstance{nullptr};
	int32 UniqueId;
};


