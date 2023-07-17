//Generated by TurboLink CodeGenerator, do not edit!
#pragma once
#include "TurboLinkGrpcMessage.h"
#include "SGoogleApi/AnnotationsMessage.h"
#include "SGoogleProtobuf/EmptyMessage.h"
#include "SSroCharacters/CharactersMessage.h"
#include "ChatMessage.generated.h"

UENUM(BlueprintType, meta = (DisplayName="SroChat.UpdateChatChannelRequest._name"))
enum class EGrpcSroChatUpdateChatChannelRequest_name : uint8
{
    Name=0,
};

UENUM(BlueprintType, meta = (DisplayName="SroChat.UpdateChatChannelRequest._dimension"))
enum class EGrpcSroChatUpdateChatChannelRequest_dimension : uint8
{
    Dimension=0,
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.RequestChatChannelAuthChange"))
struct FGrpcSroChatRequestChatChannelAuthChange : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FGrpcSroCharactersCharacterTarget Character;

    UPROPERTY(BlueprintReadWrite)
    bool Add = false;

    UPROPERTY(BlueprintReadWrite)
    TArray<FUInt64> Ids;
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.ChatChannel"))
struct FGrpcSroChatChatChannel : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FUInt64 Id = 0;

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";

    UPROPERTY(BlueprintReadWrite)
    FString Dimension = "";
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.ChatChannels"))
struct FGrpcSroChatChatChannels : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TArray<FGrpcSroChatChatChannel> Channels;
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.CreateChannelMessage"))
struct FGrpcSroChatCreateChannelMessage : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";

    UPROPERTY(BlueprintReadWrite)
    FString Dimension = "";
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.ChatChannelTarget"))
struct FGrpcSroChatChatChannelTarget : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FUInt64 Id = 0;
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.ChatMessage"))
struct FGrpcSroChatChatMessage : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Message = "";

    UPROPERTY(BlueprintReadWrite)
    FString CharacterName = "";
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.SendChatMessageRequest"))
struct FGrpcSroChatSendChatMessageRequest : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FUInt64 ChannelId = 0;

    UPROPERTY(BlueprintReadWrite)
    FGrpcSroChatChatMessage ChatMessage;
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.SendDirectMessageRequest"))
struct FGrpcSroChatSendDirectMessageRequest : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FGrpcSroCharactersCharacterTarget Target;

    UPROPERTY(BlueprintReadWrite)
    FGrpcSroChatChatMessage ChatMessage;
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.UpdateChatChannelRequest._name",
    HasNativeMake = "TurboLinkGrpc.GrpcSroChatUpdateChatChannelRequest_nameHelperLibrary.Make_name",
    HasNativeBreak = "TurboLinkGrpc.GrpcSroChatUpdateChatChannelRequest_nameHelperLibrary.Break_name"))
struct FGrpcSroChatUpdateChatChannelRequest_name : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    EGrpcSroChatUpdateChatChannelRequest_name _nameCase;

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.UpdateChatChannelRequest._dimension",
    HasNativeMake = "TurboLinkGrpc.GrpcSroChatUpdateChatChannelRequest_dimensionHelperLibrary.Make_dimension",
    HasNativeBreak = "TurboLinkGrpc.GrpcSroChatUpdateChatChannelRequest_dimensionHelperLibrary.Break_dimension"))
struct FGrpcSroChatUpdateChatChannelRequest_dimension : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    EGrpcSroChatUpdateChatChannelRequest_dimension _dimensionCase;

    UPROPERTY(BlueprintReadWrite)
    FString Dimension = "";
};

USTRUCT(BlueprintType, meta = (DisplayName="SroChat.UpdateChatChannelRequest"))
struct FGrpcSroChatUpdateChatChannelRequest : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FUInt64 ChannelId = 0;

    UPROPERTY(BlueprintReadWrite)
    FGrpcSroChatUpdateChatChannelRequest_name _name;

    UPROPERTY(BlueprintReadWrite)
    FGrpcSroChatUpdateChatChannelRequest_dimension _dimension;
};

UCLASS()
class UGrpcSroChatUpdateChatChannelRequest_nameHelperLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "TurboLink|SroChat", meta=(BlueprintThreadSafe))
    static FGrpcSroChatUpdateChatChannelRequest_name Make_name(EGrpcSroChatUpdateChatChannelRequest_name _nameCase, 
        FString Name 
    );

    UFUNCTION(BlueprintPure, Category = "TurboLink|SroChat", meta=(BlueprintThreadSafe))
    static void Break_name(const FGrpcSroChatUpdateChatChannelRequest_name& _name, EGrpcSroChatUpdateChatChannelRequest_name& _nameCase, 
        FString& Name 
    );
};

UCLASS()
class UGrpcSroChatUpdateChatChannelRequest_dimensionHelperLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "TurboLink|SroChat", meta=(BlueprintThreadSafe))
    static FGrpcSroChatUpdateChatChannelRequest_dimension Make_dimension(EGrpcSroChatUpdateChatChannelRequest_dimension _dimensionCase, 
        FString Dimension 
    );

    UFUNCTION(BlueprintPure, Category = "TurboLink|SroChat", meta=(BlueprintThreadSafe))
    static void Break_dimension(const FGrpcSroChatUpdateChatChannelRequest_dimension& _dimension, EGrpcSroChatUpdateChatChannelRequest_dimension& _dimensionCase, 
        FString& Dimension 
    );
};