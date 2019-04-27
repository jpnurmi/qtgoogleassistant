// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/type/latlng.proto

#include "google/type/latlng.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace google {
namespace type {
class LatLngDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<LatLng>
      _instance;
} _LatLng_default_instance_;
}  // namespace type
}  // namespace google
namespace protobuf_google_2ftype_2flatlng_2eproto {
static void InitDefaultsLatLng() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::google::type::_LatLng_default_instance_;
    new (ptr) ::google::type::LatLng();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::google::type::LatLng::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_LatLng =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsLatLng}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_LatLng.base);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::google::type::LatLng, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::google::type::LatLng, latitude_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::google::type::LatLng, longitude_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::google::type::LatLng)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::google::type::_LatLng_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "google/type/latlng.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\030google/type/latlng.proto\022\013google.type\""
      "-\n\006LatLng\022\020\n\010latitude\030\001 \001(\001\022\021\n\tlongitude"
      "\030\002 \001(\001Bc\n\017com.google.typeB\013LatLngProtoP\001"
      "Z8google.golang.org/genproto/googleapis/"
      "type/latlng;latlng\370\001\001\242\002\003GTPb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 195);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "google/type/latlng.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_google_2ftype_2flatlng_2eproto
namespace google {
namespace type {

// ===================================================================

void LatLng::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int LatLng::kLatitudeFieldNumber;
const int LatLng::kLongitudeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

LatLng::LatLng()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_google_2ftype_2flatlng_2eproto::scc_info_LatLng.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:google.type.LatLng)
}
LatLng::LatLng(::google::protobuf::Arena* arena)
  : ::google::protobuf::Message(),
  _internal_metadata_(arena) {
  ::google::protobuf::internal::InitSCC(&protobuf_google_2ftype_2flatlng_2eproto::scc_info_LatLng.base);
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:google.type.LatLng)
}
LatLng::LatLng(const LatLng& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&latitude_, &from.latitude_,
    static_cast<size_t>(reinterpret_cast<char*>(&longitude_) -
    reinterpret_cast<char*>(&latitude_)) + sizeof(longitude_));
  // @@protoc_insertion_point(copy_constructor:google.type.LatLng)
}

void LatLng::SharedCtor() {
  ::memset(&latitude_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&longitude_) -
      reinterpret_cast<char*>(&latitude_)) + sizeof(longitude_));
}

LatLng::~LatLng() {
  // @@protoc_insertion_point(destructor:google.type.LatLng)
  SharedDtor();
}

void LatLng::SharedDtor() {
  GOOGLE_DCHECK(GetArenaNoVirtual() == NULL);
}

void LatLng::ArenaDtor(void* object) {
  LatLng* _this = reinterpret_cast< LatLng* >(object);
  (void)_this;
}
void LatLng::RegisterArenaDtor(::google::protobuf::Arena* arena) {
}
void LatLng::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* LatLng::descriptor() {
  ::protobuf_google_2ftype_2flatlng_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_google_2ftype_2flatlng_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const LatLng& LatLng::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_google_2ftype_2flatlng_2eproto::scc_info_LatLng.base);
  return *internal_default_instance();
}


void LatLng::Clear() {
// @@protoc_insertion_point(message_clear_start:google.type.LatLng)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&latitude_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&longitude_) -
      reinterpret_cast<char*>(&latitude_)) + sizeof(longitude_));
  _internal_metadata_.Clear();
}

bool LatLng::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:google.type.LatLng)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // double latitude = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(9u /* 9 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &latitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double longitude = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(17u /* 17 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &longitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:google.type.LatLng)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:google.type.LatLng)
  return false;
#undef DO_
}

void LatLng::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:google.type.LatLng)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double latitude = 1;
  if (this->latitude() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->latitude(), output);
  }

  // double longitude = 2;
  if (this->longitude() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->longitude(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:google.type.LatLng)
}

::google::protobuf::uint8* LatLng::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:google.type.LatLng)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double latitude = 1;
  if (this->latitude() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->latitude(), target);
  }

  // double longitude = 2;
  if (this->longitude() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->longitude(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:google.type.LatLng)
  return target;
}

size_t LatLng::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:google.type.LatLng)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // double latitude = 1;
  if (this->latitude() != 0) {
    total_size += 1 + 8;
  }

  // double longitude = 2;
  if (this->longitude() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void LatLng::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:google.type.LatLng)
  GOOGLE_DCHECK_NE(&from, this);
  const LatLng* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const LatLng>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:google.type.LatLng)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:google.type.LatLng)
    MergeFrom(*source);
  }
}

void LatLng::MergeFrom(const LatLng& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:google.type.LatLng)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.latitude() != 0) {
    set_latitude(from.latitude());
  }
  if (from.longitude() != 0) {
    set_longitude(from.longitude());
  }
}

void LatLng::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:google.type.LatLng)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LatLng::CopyFrom(const LatLng& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:google.type.LatLng)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LatLng::IsInitialized() const {
  return true;
}

void LatLng::Swap(LatLng* other) {
  if (other == this) return;
  if (GetArenaNoVirtual() == other->GetArenaNoVirtual()) {
    InternalSwap(other);
  } else {
    LatLng* temp = New(GetArenaNoVirtual());
    temp->MergeFrom(*other);
    other->CopyFrom(*this);
    InternalSwap(temp);
    if (GetArenaNoVirtual() == NULL) {
      delete temp;
    }
  }
}
void LatLng::UnsafeArenaSwap(LatLng* other) {
  if (other == this) return;
  GOOGLE_DCHECK(GetArenaNoVirtual() == other->GetArenaNoVirtual());
  InternalSwap(other);
}
void LatLng::InternalSwap(LatLng* other) {
  using std::swap;
  swap(latitude_, other->latitude_);
  swap(longitude_, other->longitude_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata LatLng::GetMetadata() const {
  protobuf_google_2ftype_2flatlng_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_google_2ftype_2flatlng_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace type
}  // namespace google
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::google::type::LatLng* Arena::CreateMaybeMessage< ::google::type::LatLng >(Arena* arena) {
  return Arena::CreateMessageInternal< ::google::type::LatLng >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
