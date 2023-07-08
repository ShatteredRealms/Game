//Generated by TurboLink CodeGenerator, do not edit!
#include "HttpMarshaling.h"

void GRPC_TO_TURBOLINK(const ::google::api::Http* in, FGrpcGoogleApiHttp* out)
{
    out->Rules.Empty();
    for (int i=0; i<in->rules_size(); ++i) {
        FGrpcGoogleApiHttpRule field;
        GRPC_TO_TURBOLINK(&(in->rules(i)), &field);
        out->Rules.Add(MakeShareable(new FGrpcGoogleApiHttpRule(field)));
    }
}

void TURBOLINK_TO_GRPC(const FGrpcGoogleApiHttp* in, ::google::api::Http* out)
{
    for(const auto& value : in->Rules) {
        TURBOLINK_TO_GRPC(value.Get(), out->add_rules());
    } 
}

void GRPC_TO_TURBOLINK(const ::google::api::HttpRule* in, FGrpcGoogleApiHttpRule* out)
{
    out->Selector=UTF8_TO_TCHAR(in->selector().c_str());
    switch(in->pattern_case())
    {
    case ::google::api::HttpRule::kGet:
        out->Pattern.Get=UTF8_TO_TCHAR(in->get().c_str());
        out->Pattern.PatternCase = EGrpcGoogleApiHttpRulePattern::Get;
        break;
    case ::google::api::HttpRule::kPut:
        out->Pattern.Put=UTF8_TO_TCHAR(in->put().c_str());
        out->Pattern.PatternCase = EGrpcGoogleApiHttpRulePattern::Put;
        break;
    case ::google::api::HttpRule::kPost:
        out->Pattern.Post=UTF8_TO_TCHAR(in->post().c_str());
        out->Pattern.PatternCase = EGrpcGoogleApiHttpRulePattern::Post;
        break;
    case ::google::api::HttpRule::kDelete:
        out->Pattern.Delete=UTF8_TO_TCHAR(in->delete_().c_str());
        out->Pattern.PatternCase = EGrpcGoogleApiHttpRulePattern::Delete;
        break;
    case ::google::api::HttpRule::kPatch:
        out->Pattern.Patch=UTF8_TO_TCHAR(in->patch().c_str());
        out->Pattern.PatternCase = EGrpcGoogleApiHttpRulePattern::Patch;
        break;
    case ::google::api::HttpRule::kCustom:
    {
        FGrpcGoogleApiCustomHttpPattern field;
        GRPC_TO_TURBOLINK(&(in->custom()), &field);
        out->Pattern.Custom=MakeShareable(new FGrpcGoogleApiCustomHttpPattern(field));
        out->Pattern.PatternCase = EGrpcGoogleApiHttpRulePattern::Custom;
    }
        break;
    }
    out->Body=UTF8_TO_TCHAR(in->body().c_str());
    out->AdditionalBindings.Empty();
    for (int i=0; i<in->additional_bindings_size(); ++i) {
        FGrpcGoogleApiHttpRule field;
        GRPC_TO_TURBOLINK(&(in->additional_bindings(i)), &field);
        out->AdditionalBindings.Add(MakeShareable(new FGrpcGoogleApiHttpRule(field)));
    }
}

void TURBOLINK_TO_GRPC(const FGrpcGoogleApiHttpRule* in, ::google::api::HttpRule* out)
{
    out->set_selector(TCHAR_TO_UTF8(*(in->Selector)));
    switch (in->Pattern.PatternCase)
    {
    case EGrpcGoogleApiHttpRulePattern::Get:
        out->set_get(TCHAR_TO_UTF8(*(in->Pattern.Get)));
        break;
    case EGrpcGoogleApiHttpRulePattern::Put:
        out->set_put(TCHAR_TO_UTF8(*(in->Pattern.Put)));
        break;
    case EGrpcGoogleApiHttpRulePattern::Post:
        out->set_post(TCHAR_TO_UTF8(*(in->Pattern.Post)));
        break;
    case EGrpcGoogleApiHttpRulePattern::Delete:
        out->set_delete_(TCHAR_TO_UTF8(*(in->Pattern.Delete)));
        break;
    case EGrpcGoogleApiHttpRulePattern::Patch:
        out->set_patch(TCHAR_TO_UTF8(*(in->Pattern.Patch)));
        break;
    case EGrpcGoogleApiHttpRulePattern::Custom:
        TURBOLINK_TO_GRPC(in->Pattern.Custom.Get(), out->mutable_custom());
        break;
    }
    out->set_body(TCHAR_TO_UTF8(*(in->Body)));
    for(const auto& value : in->AdditionalBindings) {
        TURBOLINK_TO_GRPC(value.Get(), out->add_additional_bindings());
    } 
}

void GRPC_TO_TURBOLINK(const ::google::api::CustomHttpPattern* in, FGrpcGoogleApiCustomHttpPattern* out)
{
    out->Kind=UTF8_TO_TCHAR(in->kind().c_str());
    out->Path=UTF8_TO_TCHAR(in->path().c_str());
}

void TURBOLINK_TO_GRPC(const FGrpcGoogleApiCustomHttpPattern* in, ::google::api::CustomHttpPattern* out)
{
    out->set_kind(TCHAR_TO_UTF8(*(in->Kind)));
    out->set_path(TCHAR_TO_UTF8(*(in->Path)));
}

