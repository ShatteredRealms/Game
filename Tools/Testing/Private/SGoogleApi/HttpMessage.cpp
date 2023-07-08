//Generated by TurboLink CodeGenerator, do not edit!
#include "SGoogleApi/HttpMessage.h"

FGrpcGoogleApiHttp UGrpcGoogleApiHttpHelperLibrary::MakeHttp( 
    TArray<FGrpcGoogleApiHttpRule> Rules 
)
{
    FGrpcGoogleApiHttp Http;
    for (const auto& element : Rules)
    {
        Http.Rules.Add(MakeShareable(new FGrpcGoogleApiHttpRule(element)));
    }

    return Http;
}

void UGrpcGoogleApiHttpHelperLibrary::BreakHttp(const FGrpcGoogleApiHttp& Http,  
    TArray<FGrpcGoogleApiHttpRule>& Rules 
)
{
    for (auto& element : Http.Rules)
    {
        Rules.Add(*(element.Get()));
    }
}

FGrpcGoogleApiHttpRulePattern UGrpcGoogleApiHttpRulePatternHelperLibrary::MakePattern(EGrpcGoogleApiHttpRulePattern PatternCase, 
    FString Get, FString Put, FString Post, 
    FString Delete, FString Patch, FGrpcGoogleApiCustomHttpPattern Custom 
)
{
    FGrpcGoogleApiHttpRulePattern Pattern;
    Pattern.PatternCase = PatternCase;
    Pattern.Get = Get;
    Pattern.Put = Put;
    Pattern.Post = Post;
    Pattern.Delete = Delete;
    Pattern.Patch = Patch;
    Pattern.Custom = MakeShareable(new FGrpcGoogleApiCustomHttpPattern(Custom));

    return Pattern;
}

void UGrpcGoogleApiHttpRulePatternHelperLibrary::BreakPattern(const FGrpcGoogleApiHttpRulePattern& Pattern, EGrpcGoogleApiHttpRulePattern& PatternCase, 
    FString& Get, FString& Put, FString& Post, 
    FString& Delete, FString& Patch, FGrpcGoogleApiCustomHttpPattern& Custom 
)
{
    PatternCase = Pattern.PatternCase;
    Get = Pattern.Get;
    Put = Pattern.Put;
    Post = Pattern.Post;
    Delete = Pattern.Delete;
    Patch = Pattern.Patch;
    if(Pattern.Custom.Get()) 
    {
        Custom = *(Pattern.Custom.Get());
    }
}

FGrpcGoogleApiHttpRule UGrpcGoogleApiHttpRuleHelperLibrary::MakeHttpRule( 
    FString Selector, FGrpcGoogleApiHttpRulePattern Pattern, FString Body, 
    TArray<FGrpcGoogleApiHttpRule> AdditionalBindings 
)
{
    FGrpcGoogleApiHttpRule HttpRule;
    HttpRule.Selector = Selector;
    HttpRule.Pattern = Pattern;
    HttpRule.Body = Body;
    for (const auto& element : AdditionalBindings)
    {
        HttpRule.AdditionalBindings.Add(MakeShareable(new FGrpcGoogleApiHttpRule(element)));
    }

    return HttpRule;
}

void UGrpcGoogleApiHttpRuleHelperLibrary::BreakHttpRule(const FGrpcGoogleApiHttpRule& HttpRule,  
    FString& Selector, FGrpcGoogleApiHttpRulePattern& Pattern, FString& Body, 
    TArray<FGrpcGoogleApiHttpRule>& AdditionalBindings 
)
{
    Selector = HttpRule.Selector;
    Pattern = HttpRule.Pattern;
    Body = HttpRule.Body;
    for (auto& element : HttpRule.AdditionalBindings)
    {
        AdditionalBindings.Add(*(element.Get()));
    }
}

