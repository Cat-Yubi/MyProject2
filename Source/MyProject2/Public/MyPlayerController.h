#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UChatCommunicator;
class UChatBox;

UCLASS()
class MYPROJECT2_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UChatBox> ChatBoxClass{nullptr};
protected:
	virtual void BeginPlay() override;

public:
	UChatCommunicator* GetChatCommunicatorInstance() const { return ChatCommunicatorInstance; }
	
private:
	UChatCommunicator*	ChatCommunicatorInstance{nullptr};
	UChatBox*			ChatBoxInstance{nullptr};
};
