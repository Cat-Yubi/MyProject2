#include "ChatBox.h"
#include "MyPlayerController.h"
#include "ChatCommunicator.h"

UChatBox::UChatBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UChatBox::SendMessage(const FText& ChatText)
{
	MyController->GetChatCommunicatorInstance()->RequestSendMessage(ChatText);
}

void UChatBox::SetController(AMyPlayerController* NewController)
{
	MyController = NewController;
}
