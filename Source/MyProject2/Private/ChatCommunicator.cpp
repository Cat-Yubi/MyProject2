#include "ChatCommunicator.h"
#include "ChatManager.h"
#include "MyGameState.h"
#include "LevelInstance/LevelInstanceTypes.h"

UChatCommunicator::UChatCommunicator()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UChatCommunicator::BeginPlay()
{
	Super::BeginPlay();

	if (AMyGameState* GS = GetWorld()->GetGameState<AMyGameState>())
	{
		if (GS->GetChatManager())
		{
			ChatManagerInstance = GS->GetChatManager();

			if (GetNetMode() == NM_Client)
				ServerSetCommunicator(this);
		}
		else
		{
			GS->OnChatManagerReplicated.AddDynamic(this, &UChatCommunicator::OnReceiveChatManager);
		}
	}
}

void UChatCommunicator::RequestSendMessage(const FText& ChatText)
{
	ServerSendMessage(UniqueId, ChatText);
}

void UChatCommunicator::ClientNotice_Implementation(const FString& Message)
{
	ScreenDebugMessage(Message);
}

void UChatCommunicator::ClientResultId_Implementation(int32 ClientId)
{
	UniqueId = ClientId;
}

void UChatCommunicator::ServerSendMessage_Implementation(int32 SendId, const FText& ChatText)
{
	if (ChatManagerInstance)
		ChatManagerInstance->ServerSendMessage(UniqueId, ChatText);
}

void UChatCommunicator::ServerSetCommunicator_Implementation(UChatCommunicator* Communicator)
{
	if (ChatManagerInstance)
		ChatManagerInstance->ServerAddCommunicator(Communicator);
}

void UChatCommunicator::ScreenDebugMessage(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, Message);
}

void UChatCommunicator::OnReceiveChatManager(AChatManager* Manager)
{
	ChatManagerInstance = Manager;

	ServerSetCommunicator(this);
}
