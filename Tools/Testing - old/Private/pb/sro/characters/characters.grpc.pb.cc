// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: sro/characters/characters.proto

#include "sro/characters/characters.pb.h"
#include "sro/characters/characters.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace sro {
namespace characters {

static const char* CharactersService_method_names[] = {
  "/sro.characters.CharactersService/GetGenders",
  "/sro.characters.CharactersService/GetRealms",
  "/sro.characters.CharactersService/GetCharacters",
  "/sro.characters.CharactersService/GetCharacter",
  "/sro.characters.CharactersService/CreateCharacter",
  "/sro.characters.CharactersService/DeleteCharacter",
  "/sro.characters.CharactersService/GetAllCharactersForUser",
  "/sro.characters.CharactersService/EditCharacter",
  "/sro.characters.CharactersService/AddCharacterPlayTime",
};

std::unique_ptr< CharactersService::Stub> CharactersService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< CharactersService::Stub> stub(new CharactersService::Stub(channel, options));
  return stub;
}

CharactersService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_GetGenders_(CharactersService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetRealms_(CharactersService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetCharacters_(CharactersService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetCharacter_(CharactersService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CreateCharacter_(CharactersService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DeleteCharacter_(CharactersService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetAllCharactersForUser_(CharactersService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_EditCharacter_(CharactersService_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AddCharacterPlayTime_(CharactersService_method_names[8], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status CharactersService::Stub::GetGenders(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::sro::characters::Genders* response) {
  return ::grpc::internal::BlockingUnaryCall< ::google::protobuf::Empty, ::sro::characters::Genders, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetGenders_, context, request, response);
}

void CharactersService::Stub::async::GetGenders(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::sro::characters::Genders* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::google::protobuf::Empty, ::sro::characters::Genders, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetGenders_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::GetGenders(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::sro::characters::Genders* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetGenders_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::Genders>* CharactersService::Stub::PrepareAsyncGetGendersRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::sro::characters::Genders, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetGenders_, context, request);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::Genders>* CharactersService::Stub::AsyncGetGendersRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetGendersRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::GetRealms(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::sro::characters::Realms* response) {
  return ::grpc::internal::BlockingUnaryCall< ::google::protobuf::Empty, ::sro::characters::Realms, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetRealms_, context, request, response);
}

void CharactersService::Stub::async::GetRealms(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::sro::characters::Realms* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::google::protobuf::Empty, ::sro::characters::Realms, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetRealms_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::GetRealms(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::sro::characters::Realms* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetRealms_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::Realms>* CharactersService::Stub::PrepareAsyncGetRealmsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::sro::characters::Realms, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetRealms_, context, request);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::Realms>* CharactersService::Stub::AsyncGetRealmsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetRealmsRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::GetCharacters(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::sro::characters::CharactersResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::google::protobuf::Empty, ::sro::characters::CharactersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetCharacters_, context, request, response);
}

void CharactersService::Stub::async::GetCharacters(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::sro::characters::CharactersResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::google::protobuf::Empty, ::sro::characters::CharactersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetCharacters_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::GetCharacters(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::sro::characters::CharactersResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetCharacters_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharactersResponse>* CharactersService::Stub::PrepareAsyncGetCharactersRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::sro::characters::CharactersResponse, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetCharacters_, context, request);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharactersResponse>* CharactersService::Stub::AsyncGetCharactersRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetCharactersRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::GetCharacter(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget& request, ::sro::characters::CharacterResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::sro::characters::CharacterTarget, ::sro::characters::CharacterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetCharacter_, context, request, response);
}

void CharactersService::Stub::async::GetCharacter(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget* request, ::sro::characters::CharacterResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::sro::characters::CharacterTarget, ::sro::characters::CharacterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetCharacter_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::GetCharacter(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget* request, ::sro::characters::CharacterResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetCharacter_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharacterResponse>* CharactersService::Stub::PrepareAsyncGetCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::sro::characters::CharacterResponse, ::sro::characters::CharacterTarget, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetCharacter_, context, request);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharacterResponse>* CharactersService::Stub::AsyncGetCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetCharacterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::CreateCharacter(::grpc::ClientContext* context, const ::sro::characters::CreateCharacterRequest& request, ::sro::characters::CharacterResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::sro::characters::CreateCharacterRequest, ::sro::characters::CharacterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CreateCharacter_, context, request, response);
}

void CharactersService::Stub::async::CreateCharacter(::grpc::ClientContext* context, const ::sro::characters::CreateCharacterRequest* request, ::sro::characters::CharacterResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::sro::characters::CreateCharacterRequest, ::sro::characters::CharacterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateCharacter_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::CreateCharacter(::grpc::ClientContext* context, const ::sro::characters::CreateCharacterRequest* request, ::sro::characters::CharacterResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateCharacter_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharacterResponse>* CharactersService::Stub::PrepareAsyncCreateCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::CreateCharacterRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::sro::characters::CharacterResponse, ::sro::characters::CreateCharacterRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CreateCharacter_, context, request);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharacterResponse>* CharactersService::Stub::AsyncCreateCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::CreateCharacterRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCreateCharacterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::DeleteCharacter(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::sro::characters::CharacterTarget, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_DeleteCharacter_, context, request, response);
}

void CharactersService::Stub::async::DeleteCharacter(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::sro::characters::CharacterTarget, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DeleteCharacter_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::DeleteCharacter(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DeleteCharacter_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* CharactersService::Stub::PrepareAsyncDeleteCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::sro::characters::CharacterTarget, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_DeleteCharacter_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* CharactersService::Stub::AsyncDeleteCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::CharacterTarget& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncDeleteCharacterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::GetAllCharactersForUser(::grpc::ClientContext* context, const ::sro::UserTarget& request, ::sro::characters::CharactersResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::sro::UserTarget, ::sro::characters::CharactersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetAllCharactersForUser_, context, request, response);
}

void CharactersService::Stub::async::GetAllCharactersForUser(::grpc::ClientContext* context, const ::sro::UserTarget* request, ::sro::characters::CharactersResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::sro::UserTarget, ::sro::characters::CharactersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetAllCharactersForUser_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::GetAllCharactersForUser(::grpc::ClientContext* context, const ::sro::UserTarget* request, ::sro::characters::CharactersResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetAllCharactersForUser_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharactersResponse>* CharactersService::Stub::PrepareAsyncGetAllCharactersForUserRaw(::grpc::ClientContext* context, const ::sro::UserTarget& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::sro::characters::CharactersResponse, ::sro::UserTarget, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetAllCharactersForUser_, context, request);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::CharactersResponse>* CharactersService::Stub::AsyncGetAllCharactersForUserRaw(::grpc::ClientContext* context, const ::sro::UserTarget& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetAllCharactersForUserRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::EditCharacter(::grpc::ClientContext* context, const ::sro::characters::EditCharacterRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::sro::characters::EditCharacterRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_EditCharacter_, context, request, response);
}

void CharactersService::Stub::async::EditCharacter(::grpc::ClientContext* context, const ::sro::characters::EditCharacterRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::sro::characters::EditCharacterRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_EditCharacter_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::EditCharacter(::grpc::ClientContext* context, const ::sro::characters::EditCharacterRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_EditCharacter_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* CharactersService::Stub::PrepareAsyncEditCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::EditCharacterRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::sro::characters::EditCharacterRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_EditCharacter_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* CharactersService::Stub::AsyncEditCharacterRaw(::grpc::ClientContext* context, const ::sro::characters::EditCharacterRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncEditCharacterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CharactersService::Stub::AddCharacterPlayTime(::grpc::ClientContext* context, const ::sro::characters::AddPlayTimeRequest& request, ::sro::characters::PlayTimeResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::sro::characters::AddPlayTimeRequest, ::sro::characters::PlayTimeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_AddCharacterPlayTime_, context, request, response);
}

void CharactersService::Stub::async::AddCharacterPlayTime(::grpc::ClientContext* context, const ::sro::characters::AddPlayTimeRequest* request, ::sro::characters::PlayTimeResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::sro::characters::AddPlayTimeRequest, ::sro::characters::PlayTimeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddCharacterPlayTime_, context, request, response, std::move(f));
}

void CharactersService::Stub::async::AddCharacterPlayTime(::grpc::ClientContext* context, const ::sro::characters::AddPlayTimeRequest* request, ::sro::characters::PlayTimeResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddCharacterPlayTime_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::PlayTimeResponse>* CharactersService::Stub::PrepareAsyncAddCharacterPlayTimeRaw(::grpc::ClientContext* context, const ::sro::characters::AddPlayTimeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::sro::characters::PlayTimeResponse, ::sro::characters::AddPlayTimeRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_AddCharacterPlayTime_, context, request);
}

::grpc::ClientAsyncResponseReader< ::sro::characters::PlayTimeResponse>* CharactersService::Stub::AsyncAddCharacterPlayTimeRaw(::grpc::ClientContext* context, const ::sro::characters::AddPlayTimeRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncAddCharacterPlayTimeRaw(context, request, cq);
  result->StartCall();
  return result;
}

CharactersService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::google::protobuf::Empty, ::sro::characters::Genders, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::google::protobuf::Empty* req,
             ::sro::characters::Genders* resp) {
               return service->GetGenders(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::google::protobuf::Empty, ::sro::characters::Realms, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::google::protobuf::Empty* req,
             ::sro::characters::Realms* resp) {
               return service->GetRealms(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::google::protobuf::Empty, ::sro::characters::CharactersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::google::protobuf::Empty* req,
             ::sro::characters::CharactersResponse* resp) {
               return service->GetCharacters(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::sro::characters::CharacterTarget, ::sro::characters::CharacterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::sro::characters::CharacterTarget* req,
             ::sro::characters::CharacterResponse* resp) {
               return service->GetCharacter(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::sro::characters::CreateCharacterRequest, ::sro::characters::CharacterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::sro::characters::CreateCharacterRequest* req,
             ::sro::characters::CharacterResponse* resp) {
               return service->CreateCharacter(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::sro::characters::CharacterTarget, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::sro::characters::CharacterTarget* req,
             ::google::protobuf::Empty* resp) {
               return service->DeleteCharacter(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::sro::UserTarget, ::sro::characters::CharactersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::sro::UserTarget* req,
             ::sro::characters::CharactersResponse* resp) {
               return service->GetAllCharactersForUser(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::sro::characters::EditCharacterRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::sro::characters::EditCharacterRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->EditCharacter(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CharactersService_method_names[8],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CharactersService::Service, ::sro::characters::AddPlayTimeRequest, ::sro::characters::PlayTimeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CharactersService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::sro::characters::AddPlayTimeRequest* req,
             ::sro::characters::PlayTimeResponse* resp) {
               return service->AddCharacterPlayTime(ctx, req, resp);
             }, this)));
}

CharactersService::Service::~Service() {
}

::grpc::Status CharactersService::Service::GetGenders(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::sro::characters::Genders* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::GetRealms(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::sro::characters::Realms* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::GetCharacters(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::sro::characters::CharactersResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::GetCharacter(::grpc::ServerContext* context, const ::sro::characters::CharacterTarget* request, ::sro::characters::CharacterResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::CreateCharacter(::grpc::ServerContext* context, const ::sro::characters::CreateCharacterRequest* request, ::sro::characters::CharacterResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::DeleteCharacter(::grpc::ServerContext* context, const ::sro::characters::CharacterTarget* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::GetAllCharactersForUser(::grpc::ServerContext* context, const ::sro::UserTarget* request, ::sro::characters::CharactersResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::EditCharacter(::grpc::ServerContext* context, const ::sro::characters::EditCharacterRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CharactersService::Service::AddCharacterPlayTime(::grpc::ServerContext* context, const ::sro::characters::AddPlayTimeRequest* request, ::sro::characters::PlayTimeResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace sro
}  // namespace characters

