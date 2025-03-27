#include "MyGameState.h"
#include "ChatManager.h"
#include "Net/UnrealNetwork.h"

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ChatManagerInstance = GetWorld()->SpawnActor<AChatManager>(ChatManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}
}

AChatManager* AMyGameState::GetChatManager() const
{
	return ChatManagerInstance;
}

void AMyGameState::OnRep_ChatManager() const
{
	OnChatManagerReplicated.Broadcast(ChatManagerInstance);
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameState, ChatManagerInstance);
}
