#include "Chatbot.h"
#include "Engine/Engine.h"

void UChatbot::ReceiveMessage(const FString& Message)
{
    UE_LOG(LogTemp, Log, TEXT("Received message: %s"), *Message);

    // Do something with the response (e.g., display it in a chat window)
}
