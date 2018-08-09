// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: src/modules/configure/plugin_loader.proto

#ifndef PROTOBUF_INCLUDED_src_2fmodules_2fconfigure_2fplugin_5floader_2eproto
#define PROTOBUF_INCLUDED_src_2fmodules_2fconfigure_2fplugin_5floader_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_src_2fmodules_2fconfigure_2fplugin_5floader_2eproto 

namespace protobuf_src_2fmodules_2fconfigure_2fplugin_5floader_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_src_2fmodules_2fconfigure_2fplugin_5floader_2eproto
namespace peleus {
namespace modules {
namespace configure {
class plugin_conf;
class plugin_confDefaultTypeInternal;
extern plugin_confDefaultTypeInternal _plugin_conf_default_instance_;
}  // namespace configure
}  // namespace modules
}  // namespace peleus
namespace google {
namespace protobuf {
template<> ::peleus::modules::configure::plugin_conf* Arena::CreateMaybeMessage<::peleus::modules::configure::plugin_conf>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace peleus {
namespace modules {
namespace configure {

// ===================================================================

class plugin_conf : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:peleus.modules.configure.plugin_conf) */ {
 public:
  plugin_conf();
  virtual ~plugin_conf();

  plugin_conf(const plugin_conf& from);

  inline plugin_conf& operator=(const plugin_conf& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  plugin_conf(plugin_conf&& from) noexcept
    : plugin_conf() {
    *this = ::std::move(from);
  }

  inline plugin_conf& operator=(plugin_conf&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const plugin_conf& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const plugin_conf* internal_default_instance() {
    return reinterpret_cast<const plugin_conf*>(
               &_plugin_conf_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(plugin_conf* other);
  friend void swap(plugin_conf& a, plugin_conf& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline plugin_conf* New() const final {
    return CreateMaybeMessage<plugin_conf>(NULL);
  }

  plugin_conf* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<plugin_conf>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const plugin_conf& from);
  void MergeFrom(const plugin_conf& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(plugin_conf* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string func = 1;
  bool has_func() const;
  void clear_func();
  static const int kFuncFieldNumber = 1;
  const ::std::string& func() const;
  void set_func(const ::std::string& value);
  #if LANG_CXX11
  void set_func(::std::string&& value);
  #endif
  void set_func(const char* value);
  void set_func(const char* value, size_t size);
  ::std::string* mutable_func();
  ::std::string* release_func();
  void set_allocated_func(::std::string* func);

  // required string path = 2;
  bool has_path() const;
  void clear_path();
  static const int kPathFieldNumber = 2;
  const ::std::string& path() const;
  void set_path(const ::std::string& value);
  #if LANG_CXX11
  void set_path(::std::string&& value);
  #endif
  void set_path(const char* value);
  void set_path(const char* value, size_t size);
  ::std::string* mutable_path();
  ::std::string* release_path();
  void set_allocated_path(::std::string* path);

  // required string conf_path = 3;
  bool has_conf_path() const;
  void clear_conf_path();
  static const int kConfPathFieldNumber = 3;
  const ::std::string& conf_path() const;
  void set_conf_path(const ::std::string& value);
  #if LANG_CXX11
  void set_conf_path(::std::string&& value);
  #endif
  void set_conf_path(const char* value);
  void set_conf_path(const char* value, size_t size);
  ::std::string* mutable_conf_path();
  ::std::string* release_conf_path();
  void set_allocated_conf_path(::std::string* conf_path);

  // required int32 static_flag = 4;
  bool has_static_flag() const;
  void clear_static_flag();
  static const int kStaticFlagFieldNumber = 4;
  ::google::protobuf::int32 static_flag() const;
  void set_static_flag(::google::protobuf::int32 value);

  // optional int32 error_report = 5 [default = 0];
  bool has_error_report() const;
  void clear_error_report();
  static const int kErrorReportFieldNumber = 5;
  ::google::protobuf::int32 error_report() const;
  void set_error_report(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:peleus.modules.configure.plugin_conf)
 private:
  void set_has_func();
  void clear_has_func();
  void set_has_path();
  void clear_has_path();
  void set_has_conf_path();
  void clear_has_conf_path();
  void set_has_static_flag();
  void clear_has_static_flag();
  void set_has_error_report();
  void clear_has_error_report();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr func_;
  ::google::protobuf::internal::ArenaStringPtr path_;
  ::google::protobuf::internal::ArenaStringPtr conf_path_;
  ::google::protobuf::int32 static_flag_;
  ::google::protobuf::int32 error_report_;
  friend struct ::protobuf_src_2fmodules_2fconfigure_2fplugin_5floader_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// plugin_conf

// required string func = 1;
inline bool plugin_conf::has_func() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void plugin_conf::set_has_func() {
  _has_bits_[0] |= 0x00000001u;
}
inline void plugin_conf::clear_has_func() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void plugin_conf::clear_func() {
  func_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_func();
}
inline const ::std::string& plugin_conf::func() const {
  // @@protoc_insertion_point(field_get:peleus.modules.configure.plugin_conf.func)
  return func_.GetNoArena();
}
inline void plugin_conf::set_func(const ::std::string& value) {
  set_has_func();
  func_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:peleus.modules.configure.plugin_conf.func)
}
#if LANG_CXX11
inline void plugin_conf::set_func(::std::string&& value) {
  set_has_func();
  func_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:peleus.modules.configure.plugin_conf.func)
}
#endif
inline void plugin_conf::set_func(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_func();
  func_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:peleus.modules.configure.plugin_conf.func)
}
inline void plugin_conf::set_func(const char* value, size_t size) {
  set_has_func();
  func_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:peleus.modules.configure.plugin_conf.func)
}
inline ::std::string* plugin_conf::mutable_func() {
  set_has_func();
  // @@protoc_insertion_point(field_mutable:peleus.modules.configure.plugin_conf.func)
  return func_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* plugin_conf::release_func() {
  // @@protoc_insertion_point(field_release:peleus.modules.configure.plugin_conf.func)
  if (!has_func()) {
    return NULL;
  }
  clear_has_func();
  return func_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void plugin_conf::set_allocated_func(::std::string* func) {
  if (func != NULL) {
    set_has_func();
  } else {
    clear_has_func();
  }
  func_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), func);
  // @@protoc_insertion_point(field_set_allocated:peleus.modules.configure.plugin_conf.func)
}

// required string path = 2;
inline bool plugin_conf::has_path() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void plugin_conf::set_has_path() {
  _has_bits_[0] |= 0x00000002u;
}
inline void plugin_conf::clear_has_path() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void plugin_conf::clear_path() {
  path_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_path();
}
inline const ::std::string& plugin_conf::path() const {
  // @@protoc_insertion_point(field_get:peleus.modules.configure.plugin_conf.path)
  return path_.GetNoArena();
}
inline void plugin_conf::set_path(const ::std::string& value) {
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:peleus.modules.configure.plugin_conf.path)
}
#if LANG_CXX11
inline void plugin_conf::set_path(::std::string&& value) {
  set_has_path();
  path_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:peleus.modules.configure.plugin_conf.path)
}
#endif
inline void plugin_conf::set_path(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:peleus.modules.configure.plugin_conf.path)
}
inline void plugin_conf::set_path(const char* value, size_t size) {
  set_has_path();
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:peleus.modules.configure.plugin_conf.path)
}
inline ::std::string* plugin_conf::mutable_path() {
  set_has_path();
  // @@protoc_insertion_point(field_mutable:peleus.modules.configure.plugin_conf.path)
  return path_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* plugin_conf::release_path() {
  // @@protoc_insertion_point(field_release:peleus.modules.configure.plugin_conf.path)
  if (!has_path()) {
    return NULL;
  }
  clear_has_path();
  return path_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void plugin_conf::set_allocated_path(::std::string* path) {
  if (path != NULL) {
    set_has_path();
  } else {
    clear_has_path();
  }
  path_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), path);
  // @@protoc_insertion_point(field_set_allocated:peleus.modules.configure.plugin_conf.path)
}

// required string conf_path = 3;
inline bool plugin_conf::has_conf_path() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void plugin_conf::set_has_conf_path() {
  _has_bits_[0] |= 0x00000004u;
}
inline void plugin_conf::clear_has_conf_path() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void plugin_conf::clear_conf_path() {
  conf_path_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_conf_path();
}
inline const ::std::string& plugin_conf::conf_path() const {
  // @@protoc_insertion_point(field_get:peleus.modules.configure.plugin_conf.conf_path)
  return conf_path_.GetNoArena();
}
inline void plugin_conf::set_conf_path(const ::std::string& value) {
  set_has_conf_path();
  conf_path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:peleus.modules.configure.plugin_conf.conf_path)
}
#if LANG_CXX11
inline void plugin_conf::set_conf_path(::std::string&& value) {
  set_has_conf_path();
  conf_path_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:peleus.modules.configure.plugin_conf.conf_path)
}
#endif
inline void plugin_conf::set_conf_path(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_conf_path();
  conf_path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:peleus.modules.configure.plugin_conf.conf_path)
}
inline void plugin_conf::set_conf_path(const char* value, size_t size) {
  set_has_conf_path();
  conf_path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:peleus.modules.configure.plugin_conf.conf_path)
}
inline ::std::string* plugin_conf::mutable_conf_path() {
  set_has_conf_path();
  // @@protoc_insertion_point(field_mutable:peleus.modules.configure.plugin_conf.conf_path)
  return conf_path_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* plugin_conf::release_conf_path() {
  // @@protoc_insertion_point(field_release:peleus.modules.configure.plugin_conf.conf_path)
  if (!has_conf_path()) {
    return NULL;
  }
  clear_has_conf_path();
  return conf_path_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void plugin_conf::set_allocated_conf_path(::std::string* conf_path) {
  if (conf_path != NULL) {
    set_has_conf_path();
  } else {
    clear_has_conf_path();
  }
  conf_path_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), conf_path);
  // @@protoc_insertion_point(field_set_allocated:peleus.modules.configure.plugin_conf.conf_path)
}

// required int32 static_flag = 4;
inline bool plugin_conf::has_static_flag() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void plugin_conf::set_has_static_flag() {
  _has_bits_[0] |= 0x00000008u;
}
inline void plugin_conf::clear_has_static_flag() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void plugin_conf::clear_static_flag() {
  static_flag_ = 0;
  clear_has_static_flag();
}
inline ::google::protobuf::int32 plugin_conf::static_flag() const {
  // @@protoc_insertion_point(field_get:peleus.modules.configure.plugin_conf.static_flag)
  return static_flag_;
}
inline void plugin_conf::set_static_flag(::google::protobuf::int32 value) {
  set_has_static_flag();
  static_flag_ = value;
  // @@protoc_insertion_point(field_set:peleus.modules.configure.plugin_conf.static_flag)
}

// optional int32 error_report = 5 [default = 0];
inline bool plugin_conf::has_error_report() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void plugin_conf::set_has_error_report() {
  _has_bits_[0] |= 0x00000010u;
}
inline void plugin_conf::clear_has_error_report() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void plugin_conf::clear_error_report() {
  error_report_ = 0;
  clear_has_error_report();
}
inline ::google::protobuf::int32 plugin_conf::error_report() const {
  // @@protoc_insertion_point(field_get:peleus.modules.configure.plugin_conf.error_report)
  return error_report_;
}
inline void plugin_conf::set_error_report(::google::protobuf::int32 value) {
  set_has_error_report();
  error_report_ = value;
  // @@protoc_insertion_point(field_set:peleus.modules.configure.plugin_conf.error_report)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace configure
}  // namespace modules
}  // namespace peleus

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_src_2fmodules_2fconfigure_2fplugin_5floader_2eproto
