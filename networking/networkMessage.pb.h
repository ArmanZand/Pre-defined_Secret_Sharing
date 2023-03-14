// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: networkMessage.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_networkMessage_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_networkMessage_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021010 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_networkMessage_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_networkMessage_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_networkMessage_2eproto;
class exampleMessage;
struct exampleMessageDefaultTypeInternal;
extern exampleMessageDefaultTypeInternal _exampleMessage_default_instance_;
class nodeInfo;
struct nodeInfoDefaultTypeInternal;
extern nodeInfoDefaultTypeInternal _nodeInfo_default_instance_;
class nodeInfoReply;
struct nodeInfoReplyDefaultTypeInternal;
extern nodeInfoReplyDefaultTypeInternal _nodeInfoReply_default_instance_;
class protobufMessage;
struct protobufMessageDefaultTypeInternal;
extern protobufMessageDefaultTypeInternal _protobufMessage_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::exampleMessage* Arena::CreateMaybeMessage<::exampleMessage>(Arena*);
template<> ::nodeInfo* Arena::CreateMaybeMessage<::nodeInfo>(Arena*);
template<> ::nodeInfoReply* Arena::CreateMaybeMessage<::nodeInfoReply>(Arena*);
template<> ::protobufMessage* Arena::CreateMaybeMessage<::protobufMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class protobufMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:protobufMessage) */ {
 public:
  inline protobufMessage() : protobufMessage(nullptr) {}
  ~protobufMessage() override;
  explicit PROTOBUF_CONSTEXPR protobufMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  protobufMessage(const protobufMessage& from);
  protobufMessage(protobufMessage&& from) noexcept
    : protobufMessage() {
    *this = ::std::move(from);
  }

  inline protobufMessage& operator=(const protobufMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline protobufMessage& operator=(protobufMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const protobufMessage& default_instance() {
    return *internal_default_instance();
  }
  enum CommandCase {
    kExampleMessage = 100,
    kNodeInfo = 1,
    kNodeInfoReply = 2,
    COMMAND_NOT_SET = 0,
  };

  static inline const protobufMessage* internal_default_instance() {
    return reinterpret_cast<const protobufMessage*>(
               &_protobufMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(protobufMessage& a, protobufMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(protobufMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(protobufMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  protobufMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<protobufMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const protobufMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const protobufMessage& from) {
    protobufMessage::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(protobufMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "protobufMessage";
  }
  protected:
  explicit protobufMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kExampleMessageFieldNumber = 100,
    kNodeInfoFieldNumber = 1,
    kNodeInfoReplyFieldNumber = 2,
  };
  // .exampleMessage exampleMessage = 100;
  bool has_examplemessage() const;
  private:
  bool _internal_has_examplemessage() const;
  public:
  void clear_examplemessage();
  const ::exampleMessage& examplemessage() const;
  PROTOBUF_NODISCARD ::exampleMessage* release_examplemessage();
  ::exampleMessage* mutable_examplemessage();
  void set_allocated_examplemessage(::exampleMessage* examplemessage);
  private:
  const ::exampleMessage& _internal_examplemessage() const;
  ::exampleMessage* _internal_mutable_examplemessage();
  public:
  void unsafe_arena_set_allocated_examplemessage(
      ::exampleMessage* examplemessage);
  ::exampleMessage* unsafe_arena_release_examplemessage();

  // .nodeInfo nodeInfo = 1;
  bool has_nodeinfo() const;
  private:
  bool _internal_has_nodeinfo() const;
  public:
  void clear_nodeinfo();
  const ::nodeInfo& nodeinfo() const;
  PROTOBUF_NODISCARD ::nodeInfo* release_nodeinfo();
  ::nodeInfo* mutable_nodeinfo();
  void set_allocated_nodeinfo(::nodeInfo* nodeinfo);
  private:
  const ::nodeInfo& _internal_nodeinfo() const;
  ::nodeInfo* _internal_mutable_nodeinfo();
  public:
  void unsafe_arena_set_allocated_nodeinfo(
      ::nodeInfo* nodeinfo);
  ::nodeInfo* unsafe_arena_release_nodeinfo();

  // .nodeInfoReply nodeInfoReply = 2;
  bool has_nodeinforeply() const;
  private:
  bool _internal_has_nodeinforeply() const;
  public:
  void clear_nodeinforeply();
  const ::nodeInfoReply& nodeinforeply() const;
  PROTOBUF_NODISCARD ::nodeInfoReply* release_nodeinforeply();
  ::nodeInfoReply* mutable_nodeinforeply();
  void set_allocated_nodeinforeply(::nodeInfoReply* nodeinforeply);
  private:
  const ::nodeInfoReply& _internal_nodeinforeply() const;
  ::nodeInfoReply* _internal_mutable_nodeinforeply();
  public:
  void unsafe_arena_set_allocated_nodeinforeply(
      ::nodeInfoReply* nodeinforeply);
  ::nodeInfoReply* unsafe_arena_release_nodeinforeply();

  void clear_command();
  CommandCase command_case() const;
  // @@protoc_insertion_point(class_scope:protobufMessage)
 private:
  class _Internal;
  void set_has_examplemessage();
  void set_has_nodeinfo();
  void set_has_nodeinforeply();

  inline bool has_command() const;
  inline void clear_has_command();

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    union CommandUnion {
      constexpr CommandUnion() : _constinit_{} {}
        ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized _constinit_;
      ::exampleMessage* examplemessage_;
      ::nodeInfo* nodeinfo_;
      ::nodeInfoReply* nodeinforeply_;
    } command_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    uint32_t _oneof_case_[1];

  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_networkMessage_2eproto;
};
// -------------------------------------------------------------------

class nodeInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:nodeInfo) */ {
 public:
  inline nodeInfo() : nodeInfo(nullptr) {}
  ~nodeInfo() override;
  explicit PROTOBUF_CONSTEXPR nodeInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  nodeInfo(const nodeInfo& from);
  nodeInfo(nodeInfo&& from) noexcept
    : nodeInfo() {
    *this = ::std::move(from);
  }

  inline nodeInfo& operator=(const nodeInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline nodeInfo& operator=(nodeInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const nodeInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const nodeInfo* internal_default_instance() {
    return reinterpret_cast<const nodeInfo*>(
               &_nodeInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(nodeInfo& a, nodeInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(nodeInfo* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(nodeInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  nodeInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<nodeInfo>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const nodeInfo& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const nodeInfo& from) {
    nodeInfo::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(nodeInfo* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "nodeInfo";
  }
  protected:
  explicit nodeInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
  };
  // int32 Id = 1;
  void clear_id();
  int32_t id() const;
  void set_id(int32_t value);
  private:
  int32_t _internal_id() const;
  void _internal_set_id(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:nodeInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_networkMessage_2eproto;
};
// -------------------------------------------------------------------

class nodeInfoReply final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:nodeInfoReply) */ {
 public:
  inline nodeInfoReply() : nodeInfoReply(nullptr) {}
  ~nodeInfoReply() override;
  explicit PROTOBUF_CONSTEXPR nodeInfoReply(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  nodeInfoReply(const nodeInfoReply& from);
  nodeInfoReply(nodeInfoReply&& from) noexcept
    : nodeInfoReply() {
    *this = ::std::move(from);
  }

  inline nodeInfoReply& operator=(const nodeInfoReply& from) {
    CopyFrom(from);
    return *this;
  }
  inline nodeInfoReply& operator=(nodeInfoReply&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const nodeInfoReply& default_instance() {
    return *internal_default_instance();
  }
  static inline const nodeInfoReply* internal_default_instance() {
    return reinterpret_cast<const nodeInfoReply*>(
               &_nodeInfoReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(nodeInfoReply& a, nodeInfoReply& b) {
    a.Swap(&b);
  }
  inline void Swap(nodeInfoReply* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(nodeInfoReply* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  nodeInfoReply* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<nodeInfoReply>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const nodeInfoReply& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const nodeInfoReply& from) {
    nodeInfoReply::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(nodeInfoReply* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "nodeInfoReply";
  }
  protected:
  explicit nodeInfoReply(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
  };
  // int32 Id = 1;
  void clear_id();
  int32_t id() const;
  void set_id(int32_t value);
  private:
  int32_t _internal_id() const;
  void _internal_set_id(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:nodeInfoReply)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_networkMessage_2eproto;
};
// -------------------------------------------------------------------

class exampleMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:exampleMessage) */ {
 public:
  inline exampleMessage() : exampleMessage(nullptr) {}
  ~exampleMessage() override;
  explicit PROTOBUF_CONSTEXPR exampleMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  exampleMessage(const exampleMessage& from);
  exampleMessage(exampleMessage&& from) noexcept
    : exampleMessage() {
    *this = ::std::move(from);
  }

  inline exampleMessage& operator=(const exampleMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline exampleMessage& operator=(exampleMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const exampleMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const exampleMessage* internal_default_instance() {
    return reinterpret_cast<const exampleMessage*>(
               &_exampleMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(exampleMessage& a, exampleMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(exampleMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(exampleMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  exampleMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<exampleMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const exampleMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const exampleMessage& from) {
    exampleMessage::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(exampleMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "exampleMessage";
  }
  protected:
  explicit exampleMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMessageFieldNumber = 1,
  };
  // string message = 1;
  void clear_message();
  const std::string& message() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_message(ArgT0&& arg0, ArgT... args);
  std::string* mutable_message();
  PROTOBUF_NODISCARD std::string* release_message();
  void set_allocated_message(std::string* message);
  private:
  const std::string& _internal_message() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message(const std::string& value);
  std::string* _internal_mutable_message();
  public:

  // @@protoc_insertion_point(class_scope:exampleMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr message_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_networkMessage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// protobufMessage

// .exampleMessage exampleMessage = 100;
inline bool protobufMessage::_internal_has_examplemessage() const {
  return command_case() == kExampleMessage;
}
inline bool protobufMessage::has_examplemessage() const {
  return _internal_has_examplemessage();
}
inline void protobufMessage::set_has_examplemessage() {
  _impl_._oneof_case_[0] = kExampleMessage;
}
inline void protobufMessage::clear_examplemessage() {
  if (_internal_has_examplemessage()) {
    if (GetArenaForAllocation() == nullptr) {
      delete _impl_.command_.examplemessage_;
    }
    clear_has_command();
  }
}
inline ::exampleMessage* protobufMessage::release_examplemessage() {
  // @@protoc_insertion_point(field_release:protobufMessage.exampleMessage)
  if (_internal_has_examplemessage()) {
    clear_has_command();
    ::exampleMessage* temp = _impl_.command_.examplemessage_;
    if (GetArenaForAllocation() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    _impl_.command_.examplemessage_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::exampleMessage& protobufMessage::_internal_examplemessage() const {
  return _internal_has_examplemessage()
      ? *_impl_.command_.examplemessage_
      : reinterpret_cast< ::exampleMessage&>(::_exampleMessage_default_instance_);
}
inline const ::exampleMessage& protobufMessage::examplemessage() const {
  // @@protoc_insertion_point(field_get:protobufMessage.exampleMessage)
  return _internal_examplemessage();
}
inline ::exampleMessage* protobufMessage::unsafe_arena_release_examplemessage() {
  // @@protoc_insertion_point(field_unsafe_arena_release:protobufMessage.exampleMessage)
  if (_internal_has_examplemessage()) {
    clear_has_command();
    ::exampleMessage* temp = _impl_.command_.examplemessage_;
    _impl_.command_.examplemessage_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void protobufMessage::unsafe_arena_set_allocated_examplemessage(::exampleMessage* examplemessage) {
  clear_command();
  if (examplemessage) {
    set_has_examplemessage();
    _impl_.command_.examplemessage_ = examplemessage;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:protobufMessage.exampleMessage)
}
inline ::exampleMessage* protobufMessage::_internal_mutable_examplemessage() {
  if (!_internal_has_examplemessage()) {
    clear_command();
    set_has_examplemessage();
    _impl_.command_.examplemessage_ = CreateMaybeMessage< ::exampleMessage >(GetArenaForAllocation());
  }
  return _impl_.command_.examplemessage_;
}
inline ::exampleMessage* protobufMessage::mutable_examplemessage() {
  ::exampleMessage* _msg = _internal_mutable_examplemessage();
  // @@protoc_insertion_point(field_mutable:protobufMessage.exampleMessage)
  return _msg;
}

// .nodeInfo nodeInfo = 1;
inline bool protobufMessage::_internal_has_nodeinfo() const {
  return command_case() == kNodeInfo;
}
inline bool protobufMessage::has_nodeinfo() const {
  return _internal_has_nodeinfo();
}
inline void protobufMessage::set_has_nodeinfo() {
  _impl_._oneof_case_[0] = kNodeInfo;
}
inline void protobufMessage::clear_nodeinfo() {
  if (_internal_has_nodeinfo()) {
    if (GetArenaForAllocation() == nullptr) {
      delete _impl_.command_.nodeinfo_;
    }
    clear_has_command();
  }
}
inline ::nodeInfo* protobufMessage::release_nodeinfo() {
  // @@protoc_insertion_point(field_release:protobufMessage.nodeInfo)
  if (_internal_has_nodeinfo()) {
    clear_has_command();
    ::nodeInfo* temp = _impl_.command_.nodeinfo_;
    if (GetArenaForAllocation() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    _impl_.command_.nodeinfo_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::nodeInfo& protobufMessage::_internal_nodeinfo() const {
  return _internal_has_nodeinfo()
      ? *_impl_.command_.nodeinfo_
      : reinterpret_cast< ::nodeInfo&>(::_nodeInfo_default_instance_);
}
inline const ::nodeInfo& protobufMessage::nodeinfo() const {
  // @@protoc_insertion_point(field_get:protobufMessage.nodeInfo)
  return _internal_nodeinfo();
}
inline ::nodeInfo* protobufMessage::unsafe_arena_release_nodeinfo() {
  // @@protoc_insertion_point(field_unsafe_arena_release:protobufMessage.nodeInfo)
  if (_internal_has_nodeinfo()) {
    clear_has_command();
    ::nodeInfo* temp = _impl_.command_.nodeinfo_;
    _impl_.command_.nodeinfo_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void protobufMessage::unsafe_arena_set_allocated_nodeinfo(::nodeInfo* nodeinfo) {
  clear_command();
  if (nodeinfo) {
    set_has_nodeinfo();
    _impl_.command_.nodeinfo_ = nodeinfo;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:protobufMessage.nodeInfo)
}
inline ::nodeInfo* protobufMessage::_internal_mutable_nodeinfo() {
  if (!_internal_has_nodeinfo()) {
    clear_command();
    set_has_nodeinfo();
    _impl_.command_.nodeinfo_ = CreateMaybeMessage< ::nodeInfo >(GetArenaForAllocation());
  }
  return _impl_.command_.nodeinfo_;
}
inline ::nodeInfo* protobufMessage::mutable_nodeinfo() {
  ::nodeInfo* _msg = _internal_mutable_nodeinfo();
  // @@protoc_insertion_point(field_mutable:protobufMessage.nodeInfo)
  return _msg;
}

// .nodeInfoReply nodeInfoReply = 2;
inline bool protobufMessage::_internal_has_nodeinforeply() const {
  return command_case() == kNodeInfoReply;
}
inline bool protobufMessage::has_nodeinforeply() const {
  return _internal_has_nodeinforeply();
}
inline void protobufMessage::set_has_nodeinforeply() {
  _impl_._oneof_case_[0] = kNodeInfoReply;
}
inline void protobufMessage::clear_nodeinforeply() {
  if (_internal_has_nodeinforeply()) {
    if (GetArenaForAllocation() == nullptr) {
      delete _impl_.command_.nodeinforeply_;
    }
    clear_has_command();
  }
}
inline ::nodeInfoReply* protobufMessage::release_nodeinforeply() {
  // @@protoc_insertion_point(field_release:protobufMessage.nodeInfoReply)
  if (_internal_has_nodeinforeply()) {
    clear_has_command();
    ::nodeInfoReply* temp = _impl_.command_.nodeinforeply_;
    if (GetArenaForAllocation() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    _impl_.command_.nodeinforeply_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::nodeInfoReply& protobufMessage::_internal_nodeinforeply() const {
  return _internal_has_nodeinforeply()
      ? *_impl_.command_.nodeinforeply_
      : reinterpret_cast< ::nodeInfoReply&>(::_nodeInfoReply_default_instance_);
}
inline const ::nodeInfoReply& protobufMessage::nodeinforeply() const {
  // @@protoc_insertion_point(field_get:protobufMessage.nodeInfoReply)
  return _internal_nodeinforeply();
}
inline ::nodeInfoReply* protobufMessage::unsafe_arena_release_nodeinforeply() {
  // @@protoc_insertion_point(field_unsafe_arena_release:protobufMessage.nodeInfoReply)
  if (_internal_has_nodeinforeply()) {
    clear_has_command();
    ::nodeInfoReply* temp = _impl_.command_.nodeinforeply_;
    _impl_.command_.nodeinforeply_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void protobufMessage::unsafe_arena_set_allocated_nodeinforeply(::nodeInfoReply* nodeinforeply) {
  clear_command();
  if (nodeinforeply) {
    set_has_nodeinforeply();
    _impl_.command_.nodeinforeply_ = nodeinforeply;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:protobufMessage.nodeInfoReply)
}
inline ::nodeInfoReply* protobufMessage::_internal_mutable_nodeinforeply() {
  if (!_internal_has_nodeinforeply()) {
    clear_command();
    set_has_nodeinforeply();
    _impl_.command_.nodeinforeply_ = CreateMaybeMessage< ::nodeInfoReply >(GetArenaForAllocation());
  }
  return _impl_.command_.nodeinforeply_;
}
inline ::nodeInfoReply* protobufMessage::mutable_nodeinforeply() {
  ::nodeInfoReply* _msg = _internal_mutable_nodeinforeply();
  // @@protoc_insertion_point(field_mutable:protobufMessage.nodeInfoReply)
  return _msg;
}

inline bool protobufMessage::has_command() const {
  return command_case() != COMMAND_NOT_SET;
}
inline void protobufMessage::clear_has_command() {
  _impl_._oneof_case_[0] = COMMAND_NOT_SET;
}
inline protobufMessage::CommandCase protobufMessage::command_case() const {
  return protobufMessage::CommandCase(_impl_._oneof_case_[0]);
}
// -------------------------------------------------------------------

// nodeInfo

// int32 Id = 1;
inline void nodeInfo::clear_id() {
  _impl_.id_ = 0;
}
inline int32_t nodeInfo::_internal_id() const {
  return _impl_.id_;
}
inline int32_t nodeInfo::id() const {
  // @@protoc_insertion_point(field_get:nodeInfo.Id)
  return _internal_id();
}
inline void nodeInfo::_internal_set_id(int32_t value) {
  
  _impl_.id_ = value;
}
inline void nodeInfo::set_id(int32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:nodeInfo.Id)
}

// -------------------------------------------------------------------

// nodeInfoReply

// int32 Id = 1;
inline void nodeInfoReply::clear_id() {
  _impl_.id_ = 0;
}
inline int32_t nodeInfoReply::_internal_id() const {
  return _impl_.id_;
}
inline int32_t nodeInfoReply::id() const {
  // @@protoc_insertion_point(field_get:nodeInfoReply.Id)
  return _internal_id();
}
inline void nodeInfoReply::_internal_set_id(int32_t value) {
  
  _impl_.id_ = value;
}
inline void nodeInfoReply::set_id(int32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:nodeInfoReply.Id)
}

// -------------------------------------------------------------------

// exampleMessage

// string message = 1;
inline void exampleMessage::clear_message() {
  _impl_.message_.ClearToEmpty();
}
inline const std::string& exampleMessage::message() const {
  // @@protoc_insertion_point(field_get:exampleMessage.message)
  return _internal_message();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void exampleMessage::set_message(ArgT0&& arg0, ArgT... args) {
 
 _impl_.message_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:exampleMessage.message)
}
inline std::string* exampleMessage::mutable_message() {
  std::string* _s = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:exampleMessage.message)
  return _s;
}
inline const std::string& exampleMessage::_internal_message() const {
  return _impl_.message_.Get();
}
inline void exampleMessage::_internal_set_message(const std::string& value) {
  
  _impl_.message_.Set(value, GetArenaForAllocation());
}
inline std::string* exampleMessage::_internal_mutable_message() {
  
  return _impl_.message_.Mutable(GetArenaForAllocation());
}
inline std::string* exampleMessage::release_message() {
  // @@protoc_insertion_point(field_release:exampleMessage.message)
  return _impl_.message_.Release();
}
inline void exampleMessage::set_allocated_message(std::string* message) {
  if (message != nullptr) {
    
  } else {
    
  }
  _impl_.message_.SetAllocated(message, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.message_.IsDefault()) {
    _impl_.message_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:exampleMessage.message)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_networkMessage_2eproto
