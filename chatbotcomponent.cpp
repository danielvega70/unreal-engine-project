#include "Chatbot.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Http/Public/Http.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/ConfigCacheIni.h"

void UChatbot::SendMessage(const FString& Message)
{
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetVerb("POST");
    Request->SetURL(ChatbotUrl);

    Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    FString RequestBody = FString::Printf(TEXT("{\"prompt\":\"%s\"}"), *Message);
    Request->SetContentAsString(RequestBody);

    Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
    {
        if (bSuccess && Response.IsValid())
        {
            FString ResponseText = Response->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseText);

            if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
            {
                FString ResponseMessage = JsonObject->GetStringField("choices")[0]->GetStringField("text");
                ReceiveMessage(ResponseMessage);
            }
        }
    });

    Request->ProcessRequest();
}

void UChatbot::BeginPlay()
{
    Super::BeginPlay();

    GConfig->GetString(TEXT("Chatbot"), TEXT("ApiKey"), ApiKey, GGameIni);
    GConfig->GetString(TEXT("Chatbot"), TEXT("ModelId"), ModelId, GGameIni);
    GConfig->GetString(TEXT("Chatbot"), TEXT("ChatbotUrl"), ChatbotUrl, GGameIni);
}
