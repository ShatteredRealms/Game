//Generated by TurboLink CodeGenerator, do not edit!
#pragma once
#include "TurboLinkGrpcMessage.h"
#include "HttpMessage.generated.h"

UENUM(BlueprintType, meta = (DisplayName="GoogleApi.HttpRule.Pattern"))
enum class EGrpcGoogleApiHttpRulePattern : uint8
{
    Get=0,
    Put=1,
    Post=2,
    Delete=3,
    Patch=4,
    Custom=5,
};

USTRUCT(BlueprintType, meta = (DisplayName="GoogleApi.Http",
    HasNativeMake = "TurboLinkGrpc.GrpcGoogleApiHttpHelperLibrary.MakeHttp",
    HasNativeBreak = "TurboLinkGrpc.GrpcGoogleApiHttpHelperLibrary.BreakHttp"))
struct FGrpcGoogleApiHttp : public FGrpcMessage
{
    GENERATED_BODY()

    TArray<TSharedPtr<FGrpcGoogleApiHttpRule>> Rules;
};

USTRUCT(BlueprintType, meta = (DisplayName="GoogleApi.HttpRule.Pattern",
    HasNativeMake = "TurboLinkGrpc.GrpcGoogleApiHttpRulePatternHelperLibrary.MakePattern",
    HasNativeBreak = "TurboLinkGrpc.GrpcGoogleApiHttpRulePatternHelperLibrary.BreakPattern"))
struct FGrpcGoogleApiHttpRulePattern : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    EGrpcGoogleApiHttpRulePattern PatternCase;

    UPROPERTY(BlueprintReadWrite)
    FString Get = "";

    UPROPERTY(BlueprintReadWrite)
    FString Put = "";

    UPROPERTY(BlueprintReadWrite)
    FString Post = "";

    UPROPERTY(BlueprintReadWrite)
    FString Delete = "";

    UPROPERTY(BlueprintReadWrite)
    FString Patch = "";

    TSharedPtr<FGrpcGoogleApiCustomHttpPattern> Custom;
};

USTRUCT(BlueprintType, meta = (DisplayName="GoogleApi.HttpRule",
    HasNativeMake = "TurboLinkGrpc.GrpcGoogleApiHttpRuleHelperLibrary.MakeHttpRule",
    HasNativeBreak = "TurboLinkGrpc.GrpcGoogleApiHttpRuleHelperLibrary.BreakHttpRule"))
struct FGrpcGoogleApiHttpRule : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Selector = "";

    UPROPERTY(BlueprintReadWrite)
    FGrpcGoogleApiHttpRulePattern Pattern;

    UPROPERTY(BlueprintReadWrite)
    FString Body = "";

    TArray<TSharedPtr<FGrpcGoogleApiHttpRule>> AdditionalBindings;
};

USTRUCT(BlueprintType, meta = (DisplayName="GoogleApi.CustomHttpPattern"))
struct FGrpcGoogleApiCustomHttpPattern : public FGrpcMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Kind = "";

    UPROPERTY(BlueprintReadWrite)
    FString Path = "";
};

UCLASS()
class UGrpcGoogleApiHttpHelperLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "TurboLink|GoogleApi", meta=(BlueprintThreadSafe))
    static FGrpcGoogleApiHttp MakeHttp( 
        TArray<FGrpcGoogleApiHttpRule> Rules 
    );

    UFUNCTION(BlueprintPure, Category = "TurboLink|GoogleApi", meta=(BlueprintThreadSafe))
    static void BreakHttp(const FGrpcGoogleApiHttp& Http,  
        TArray<FGrpcGoogleApiHttpRule>& Rules 
    );
};

UCLASS()
class UGrpcGoogleApiHttpRulePatternHelperLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "TurboLink|GoogleApi", meta=(BlueprintThreadSafe))
    static FGrpcGoogleApiHttpRulePattern MakePattern(EGrpcGoogleApiHttpRulePattern PatternCase, 
        FString Get, FString Put, FString Post, 
        FString Delete, FString Patch, FGrpcGoogleApiCustomHttpPattern Custom 
    );

    UFUNCTION(BlueprintPure, Category = "TurboLink|GoogleApi", meta=(BlueprintThreadSafe))
    static void BreakPattern(const FGrpcGoogleApiHttpRulePattern& Pattern, EGrpcGoogleApiHttpRulePattern& PatternCase, 
        FString& Get, FString& Put, FString& Post, 
        FString& Delete, FString& Patch, FGrpcGoogleApiCustomHttpPattern& Custom 
    );
};

UCLASS()
class UGrpcGoogleApiHttpRuleHelperLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "TurboLink|GoogleApi", meta=(BlueprintThreadSafe))
    static FGrpcGoogleApiHttpRule MakeHttpRule( 
        FString Selector, FGrpcGoogleApiHttpRulePattern Pattern, FString Body, 
        TArray<FGrpcGoogleApiHttpRule> AdditionalBindings 
    );

    UFUNCTION(BlueprintPure, Category = "TurboLink|GoogleApi", meta=(BlueprintThreadSafe))
    static void BreakHttpRule(const FGrpcGoogleApiHttpRule& HttpRule,  
        FString& Selector, FGrpcGoogleApiHttpRulePattern& Pattern, FString& Body, 
        TArray<FGrpcGoogleApiHttpRule>& AdditionalBindings 
    );
};
