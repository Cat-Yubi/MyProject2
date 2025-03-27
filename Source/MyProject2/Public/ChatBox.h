// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatBox.generated.h"

class AMyPlayerController;
/**
 * 
 */
UCLASS()
class MYPROJECT2_API UChatBox : public UUserWidget
{
	GENERATED_BODY()

public:
	UChatBox(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
	void SendMessage(const FText& ChatText);

	void SetController(AMyPlayerController* NewController);
private:
	AMyPlayerController* MyController;
};
