#include "ChatManager.h"
#include "ChatCommunicator.h"

AChatManager::AChatManager()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bAlwaysRelevant = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AChatManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChatManager::ServerSendMessage_Implementation(int32 UniqueId, const FText& ChatText)
{
	if (ChatText.ToString() == RandomString)
	{
		for (const auto Value : Communicators)
		{
			Value->ClientNotice(FString::Printf(TEXT("Winner : %s"), *RandomString));
		}		
	}
}

void AChatManager::ServerAddCommunicator_Implementation(UChatCommunicator* Communicator)
{
	if (Communicators.Contains(Communicator))	return;

	int32 InstanceId = Communicators.Num();
	Communicators.Add(Communicator);
	Communicators[InstanceId]->ClientResultId(InstanceId);
	
	if (Communicators.Num() >= 2)
	{
		TArray<int32> Numbers;
		for (int32 i = 1; i <= 9; ++i)
		{
			Numbers.Add(i);
		}

		FMath::RandInit(FDateTime::Now().GetTicks());
		Numbers = Numbers.FilterByPredicate([](int32 Num) { return Num > 0; });
		
		for (int32 i = 0; i < 3; ++i)
		{
			int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
			RandomString.Append(FString::FromInt(Numbers[Index]));
			Numbers.RemoveAt(Index);
		}

		for (const auto Value : Communicators)
		{
			Value->ClientNotice(RandomString);
		}
	}
}


