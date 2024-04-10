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
// source: sro/globals.proto

#include "sro/globals.pb.h"

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
constexpr UserTarget::UserTarget(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : _oneof_case_{}{}
struct UserTargetDefaultTypeInternal {
  constexpr UserTargetDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~UserTargetDefaultTypeInternal() {}
  union {
    UserTarget _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT UserTargetDefaultTypeInternal _UserTarget_default_instance_;
}  // namespace sro
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_sro_2fglobals_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_sro_2fglobals_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_sro_2fglobals_2eproto = nullptr;

const uint32_t TableStruct_sro_2fglobals_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::sro::UserTarget, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::sro::UserTarget, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  ::PROTOBUF_NAMESPACE_ID::internal::kInvalidFieldOffsetTag,
  PROTOBUF_FIELD_OFFSET(::sro::UserTarget, target_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::sro::UserTarget)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::sro::_UserTarget_default_instance_),
};

const char descriptor_table_protodef_sro_2fglobals_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021sro/globals.proto\022\003sro\"8\n\nUserTarget\022\014"
  "\n\002id\030\001 \001(\tH\000\022\022\n\010username\030\002 \001(\tH\000B\010\n\006targ"
  "etB\010Z\006pkg/pbb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_sro_2fglobals_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sro_2fglobals_2eproto = {
  false, false, 100, descriptor_table_protodef_sro_2fglobals_2eproto, "sro/globals.proto", 
  &descriptor_table_sro_2fglobals_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_sro_2fglobals_2eproto::offsets,
  file_level_metadata_sro_2fglobals_2eproto, file_level_enum_descriptors_sro_2fglobals_2eproto, file_level_service_descriptors_sro_2fglobals_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_sro_2fglobals_2eproto_getter() {
  return &descriptor_table_sro_2fglobals_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_sro_2fglobals_2eproto(&descriptor_table_sro_2fglobals_2eproto);
namespace sro {

// ===================================================================

class UserTarget::_Internal {
 public:
};

UserTarget::UserTarget(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:sro.UserTarget)
}
UserTarget::UserTarget(const UserTarget& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  clear_has_target();
  switch (from.target_case()) {
    case kId: {
      _internal_set_id(from._internal_id());
      break;
    }
    case kUsername: {
      _internal_set_username(from._internal_username());
      break;
    }
    case TARGET_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:sro.UserTarget)
}

inline void UserTarget::SharedCtor() {
clear_has_target();
}

UserTarget::~UserTarget() {
  // @@protoc_insertion_point(destructor:sro.UserTarget)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void UserTarget::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (has_target()) {
    clear_target();
  }
}

void UserTarget::ArenaDtor(void* object) {
  UserTarget* _this = reinterpret_cast< UserTarget* >(object);
  (void)_this;
}
void UserTarget::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void UserTarget::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void UserTarget::clear_target() {
// @@protoc_insertion_point(one_of_clear_start:sro.UserTarget)
  switch (target_case()) {
    case kId: {
      target_.id_.Destroy(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
      break;
    }
    case kUsername: {
      target_.username_.Destroy(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
      break;
    }
    case TARGET_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = TARGET_NOT_SET;
}


void UserTarget::Clear() {
// @@protoc_insertion_point(message_clear_start:sro.UserTarget)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clear_target();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* UserTarget::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_id();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "sro.UserTarget.id"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string username = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_username();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "sro.UserTarget.username"));
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

uint8_t* UserTarget::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:sro.UserTarget)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string id = 1;
  if (_internal_has_id()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_id().data(), static_cast<int>(this->_internal_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "sro.UserTarget.id");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_id(), target);
  }

  // string username = 2;
  if (_internal_has_username()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_username().data(), static_cast<int>(this->_internal_username().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "sro.UserTarget.username");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_username(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:sro.UserTarget)
  return target;
}

size_t UserTarget::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:sro.UserTarget)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  switch (target_case()) {
    // string id = 1;
    case kId: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_id());
      break;
    }
    // string username = 2;
    case kUsername: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_username());
      break;
    }
    case TARGET_NOT_SET: {
      break;
    }
  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData UserTarget::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    UserTarget::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*UserTarget::GetClassData() const { return &_class_data_; }

void UserTarget::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<UserTarget *>(to)->MergeFrom(
      static_cast<const UserTarget &>(from));
}


void UserTarget::MergeFrom(const UserTarget& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:sro.UserTarget)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.target_case()) {
    case kId: {
      _internal_set_id(from._internal_id());
      break;
    }
    case kUsername: {
      _internal_set_username(from._internal_username());
      break;
    }
    case TARGET_NOT_SET: {
      break;
    }
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void UserTarget::CopyFrom(const UserTarget& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:sro.UserTarget)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserTarget::IsInitialized() const {
  return true;
}

void UserTarget::InternalSwap(UserTarget* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(target_, other->target_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
}

::PROTOBUF_NAMESPACE_ID::Metadata UserTarget::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_sro_2fglobals_2eproto_getter, &descriptor_table_sro_2fglobals_2eproto_once,
      file_level_metadata_sro_2fglobals_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace sro
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::sro::UserTarget* Arena::CreateMaybeMessage< ::sro::UserTarget >(Arena* arena) {
  return Arena::CreateMessageInternal< ::sro::UserTarget >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>