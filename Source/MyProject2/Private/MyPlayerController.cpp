#include "MyPlayerController.h"
#include "ChatCommunicator.h"
#include "ChatBox.h"

AMyPlayerController::AMyPlayerController()
{
	ChatCommunicatorInstance = CreateDefaultSubobject<UChatCommunicator>(TEXT("ChatCommunicator"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		ChatBoxInstance = Cast<UChatBox>(CreateWidget<UUserWidget>(this, ChatBoxClass));
		if (ChatBoxInstance)
		{
			ChatBoxInstance->AddToViewport();
			ChatBoxInstance->SetController(this);
		}		
	}

	SetShowMouseCursor(true);
}