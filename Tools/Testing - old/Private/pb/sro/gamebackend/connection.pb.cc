﻿#if defined(_MSC_VER)
  #pragma warning (disable:4018) // 'expression' : signed/unsigned mismatch
  #pragma warning (disable:4065) // switch statement contains 'default' but no 'case' labels
  #pragma warning (disable:4146) // unary minus operator applied to unsigned type, result still unsigned
  #pragma warning (disable:4244) // 'conversion' conversion from 'type1' to 'type2', possible loss of data
  #pragma warning (disable:4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
  #pragma warning (disable:4267) // 'var' : conversion from 'size_t' to 'type', possible loss of data
  #pragma warning (disable:4305) // 'identifier' : truncation from 'type1' to 'type2'
  #pragma warning (disable:4307) // 'operator' : integral constant overflow
  #pragma warning (disable:4309) // 'conversion' : truncation of constant value
  #pragma warning (disable:4334) // 'operator' : result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)
  #pragma warning (disable:4355) // 'this' : used in base member initializer list
  #pragma warning (disable:4506) // no definition for inline function 'function'
  #pragma warning (disable:4800) // 'type' : forcing value to bool 'true' or 'false' (performance warning)
  #pragma warning (disable:4996) // The compiler encountered a deprecated declaration.
  #pragma warning (disable:4125) // decimal digit terminates octal escape sequence
#endif// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sro/gamebackend/connection.proto

#include "sro/gamebackend/connection.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace sro {
namespace gamebackend {
constexpr ConnectGameServerResponse::ConnectGameServerResponse(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : address_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , port_(0u){}
struct ConnectGameServerResponseDefaultTypeInternal {
  constexpr ConnectGameServerResponseDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~ConnectGameServerResponseDefaultTypeInternal() {}
  union {
    ConnectGameServerResponse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ConnectGameServerResponseDefaultTypeInternal _ConnectGameServerResponse_default_instance_;
}  // namespace gamebackend
}  // namespace sro
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_sro_2fgamebackend_2fconnection_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_sro_2fgamebackend_2fconnection_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_sro_2fgamebackend_2fconnection_2eproto = nullptr;

const uint32_t TableStruct_sro_2fgamebackend_2fconnection_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::sro::gamebackend::ConnectGameServerResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::sro::gamebackend::ConnectGameServerResponse, address_),
  PROTOBUF_FIELD_OFFSET(::sro::gamebackend::ConnectGameServerResponse, port_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::sro::gamebackend::ConnectGameServerResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::sro::gamebackend::_ConnectGameServerResponse_default_instance_),
};

const char descriptor_table_protodef_sro_2fgamebackend_2fconnection_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n sro/gamebackend/connection.proto\022\017sro."
  "gamebackend\032\034google/api/annotations.prot"
  "o\032\037sro/characters/characters.proto\":\n\031Co"
  "nnectGameServerResponse\022\017\n\007address\030\001 \001(\t"
  "\022\014\n\004port\030\002 \001(\r2\302\001\n\021ConnectionService\022\254\001\n"
  "\021ConnectGameServer\022\037.sro.characters.Char"
  "acterTarget\032*.sro.gamebackend.ConnectGam"
  "eServerResponse\"J\202\323\344\223\002D\022\035/v1/connect/cha"
  "racter/id/{id}Z#\022!/v1/connect/character/"
  "name/{name}B\010Z\006pkg/pbb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_sro_2fgamebackend_2fconnection_2eproto_deps[2] = {
  &::descriptor_table_google_2fapi_2fannotations_2eproto,
  &::descriptor_table_sro_2fcharacters_2fcharacters_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_sro_2fgamebackend_2fconnection_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sro_2fgamebackend_2fconnection_2eproto = {
  false, false, 389, descriptor_table_protodef_sro_2fgamebackend_2fconnection_2eproto, "sro/gamebackend/connection.proto", 
  &descriptor_table_sro_2fgamebackend_2fconnection_2eproto_once, descriptor_table_sro_2fgamebackend_2fconnection_2eproto_deps, 2, 1,
  schemas, file_default_instances, TableStruct_sro_2fgamebackend_2fconnection_2eproto::offsets,
  file_level_metadata_sro_2fgamebackend_2fconnection_2eproto, file_level_enum_descriptors_sro_2fgamebackend_2fconnection_2eproto, file_level_service_descriptors_sro_2fgamebackend_2fconnection_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_sro_2fgamebackend_2fconnection_2eproto_getter() {
  return &descriptor_table_sro_2fgamebackend_2fconnection_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_sro_2fgamebackend_2fconnection_2eproto(&descriptor_table_sro_2fgamebackend_2fconnection_2eproto);
namespace sro {
namespace gamebackend {

// ===================================================================

class ConnectGameServerResponse::_Internal {
 public:
};

ConnectGameServerResponse::ConnectGameServerResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:sro.gamebackend.ConnectGameServerResponse)
}
ConnectGameServerResponse::ConnectGameServerResponse(const ConnectGameServerResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  address_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    address_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_address().empty()) {
    address_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_address(), 
      GetArenaForAllocation());
  }
  port_ = from.port_;
  // @@protoc_insertion_point(copy_constructor:sro.gamebackend.ConnectGameServerResponse)
}

inline void ConnectGameServerResponse::SharedCtor() {
address_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  address_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
port_ = 0u;
}

ConnectGameServerResponse::~ConnectGameServerResponse() {
  // @@protoc_insertion_point(destructor:sro.gamebackend.ConnectGameServerResponse)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void ConnectGameServerResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  address_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ConnectGameServerResponse::ArenaDtor(void* object) {
  ConnectGameServerResponse* _this = reinterpret_cast< ConnectGameServerResponse* >(object);
  (void)_this;
}
void ConnectGameServerResponse::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ConnectGameServerResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ConnectGameServerResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:sro.gamebackend.ConnectGameServerResponse)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  address_.ClearToEmpty();
  port_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ConnectGameServerResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string address = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_address();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "sro.gamebackend.ConnectGameServerResponse.address"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 port = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          port_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* ConnectGameServerResponse::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:sro.gamebackend.ConnectGameServerResponse)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string address = 1;
  if (!this->_internal_address().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_address().data(), static_cast<int>(this->_internal_address().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "sro.gamebackend.ConnectGameServerResponse.address");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_address(), target);
  }

  // uint32 port = 2;
  if (this->_internal_port() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_port(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:sro.gamebackend.ConnectGameServerResponse)
  return target;
}

size_t ConnectGameServerResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:sro.gamebackend.ConnectGameServerResponse)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string address = 1;
  if (!this->_internal_address().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_address());
  }

  // uint32 port = 2;
  if (this->_internal_port() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_port());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ConnectGameServerResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ConnectGameServerResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ConnectGameServerResponse::GetClassData() const { return &_class_data_; }

void ConnectGameServerResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<ConnectGameServerResponse *>(to)->MergeFrom(
      static_cast<const ConnectGameServerResponse &>(from));
}


void ConnectGameServerResponse::MergeFrom(const ConnectGameServerResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:sro.gamebackend.ConnectGameServerResponse)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_address().empty()) {
    _internal_set_address(from._internal_address());
  }
  if (from._internal_port() != 0) {
    _internal_set_port(from._internal_port());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ConnectGameServerResponse::CopyFrom(const ConnectGameServerResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:sro.gamebackend.ConnectGameServerResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ConnectGameServerResponse::IsInitialized() const {
  return true;
}

void ConnectGameServerResponse::InternalSwap(ConnectGameServerResponse* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &address_, lhs_arena,
      &other->address_, rhs_arena
  );
  swap(port_, other->port_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ConnectGameServerResponse::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_sro_2fgamebackend_2fconnection_2eproto_getter, &descriptor_table_sro_2fgamebackend_2fconnection_2eproto_once,
      file_level_metadata_sro_2fgamebackend_2fconnection_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace gamebackend
}  // namespace sro
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::sro::gamebackend::ConnectGameServerResponse* Arena::CreateMaybeMessage< ::sro::gamebackend::ConnectGameServerResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::sro::gamebackend::ConnectGameServerResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
