// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

class AChatManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatManagerReplicated, AChatManager*, ChatManagerInstance);

UCLASS()
class MYPROJECT2_API AMyGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChatManager")
	TSubclassOf<AChatManager> ChatManagerClass;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	AChatManager* GetChatManager() const;
	
	FOnChatManagerReplicated OnChatManagerReplicated;
	
private:
	UFUNCTION()
	void OnRep_ChatManager() const;
	
	UPROPERTY(ReplicatedUsing = OnRep_ChatManager)
	AChatManager* ChatManagerInstance;
};
