// 商店物品，具体信息写在蓝图里了

#pragma once

#include "CoreMinimal.h"
#include "string.h
#include "StoreItem.generated.h"


USTRUCT(BlueprintType)
struct FHerosAttribute
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = "Store")
    string Attribute;
    
    UPROPERTY(EditAnywhere, Category = "Store")
    float Value;
};

USTRUCT(BlueprintType)
struct FItemTooltipData
{
    GENERATED_BODY()
    
public:
    UPROPERTY(BlueprintReadOnly)
    FString Key;
    UPROPERTY(BlueprintReadOnly)
    FString Value;
    
    FStoreItemData(const FString& InKey, const FString InValue)
    : Key(InKey)
    , Value(InValue)
    {};
};

UCLASS()
class ARENAOFVALOR_API UStoreItem : public UItemBase
{
    GENERATED_BODY()
public:
    
    UPROPERTY(EditAnywhere, Category = "Store")
    TArray<FHerosAttribute> AttributesModify;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Store")
    UTexture2D* Icon;
    
    virtual TArray<FStoreItemData> GetItemData()
    {
        TArray<FStoreItemData> Data;
        return Data;
    }
};
