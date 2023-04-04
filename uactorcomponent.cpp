#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "UObject/UObjectGlobals.h"
#include "Chatbot.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class YOURGAME_API UChatbot : public UActorComponent
{
    GENERATED_BODY()

public:
    void SendMessage(const FString& Message);

protected:
    virtual void BeginPlay() override;

private:
    void ReceiveMessage(const FString& Message);

    FString ApiKey;
    FString ModelId;
    FString ChatbotUrl;
};
