// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Foo.proto

#ifndef PROTOBUF_Foo_2eproto__INCLUDED
#define PROTOBUF_Foo_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Foo_2eproto();
void protobuf_AssignDesc_Foo_2eproto();
void protobuf_ShutdownFile_Foo_2eproto();

class Foo;
class Foo_Bar;

// ===================================================================

class Foo_Bar : public ::google::protobuf::Message {
 public:
  Foo_Bar();
  virtual ~Foo_Bar();
  
  Foo_Bar(const Foo_Bar& from);
  
  inline Foo_Bar& operator=(const Foo_Bar& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Foo_Bar& default_instance();
  
  void Swap(Foo_Bar* other);
  
  // implements Message ----------------------------------------------
  
  Foo_Bar* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Foo_Bar& from);
  void MergeFrom(const Foo_Bar& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required double dou = 1;
  inline bool has_dou() const;
  inline void clear_dou();
  static const int kDouFieldNumber = 1;
  inline double dou() const;
  inline void set_dou(double value);
  
  // optional string text = 2;
  inline bool has_text() const;
  inline void clear_text();
  static const int kTextFieldNumber = 2;
  inline const ::std::string& text() const;
  inline void set_text(const ::std::string& value);
  inline void set_text(const char* value);
  inline void set_text(const char* value, size_t size);
  inline ::std::string* mutable_text();
  
  // @@protoc_insertion_point(class_scope:Foo.Bar)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  double dou_;
  ::std::string* text_;
  static const ::std::string _default_text_;
  friend void  protobuf_AddDesc_Foo_2eproto();
  friend void protobuf_AssignDesc_Foo_2eproto();
  friend void protobuf_ShutdownFile_Foo_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Foo_Bar* default_instance_;
};
// -------------------------------------------------------------------

class Foo : public ::google::protobuf::Message {
 public:
  Foo();
  virtual ~Foo();
  
  Foo(const Foo& from);
  
  inline Foo& operator=(const Foo& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Foo& default_instance();
  
  void Swap(Foo* other);
  
  // implements Message ----------------------------------------------
  
  Foo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Foo& from);
  void MergeFrom(const Foo& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Foo_Bar Bar;
  
  // accessors -------------------------------------------------------
  
  // optional string text = 1;
  inline bool has_text() const;
  inline void clear_text();
  static const int kTextFieldNumber = 1;
  inline const ::std::string& text() const;
  inline void set_text(const ::std::string& value);
  inline void set_text(const char* value);
  inline void set_text(const char* value, size_t size);
  inline ::std::string* mutable_text();
  
  // repeated string text_repeated = 2;
  inline int text_repeated_size() const;
  inline void clear_text_repeated();
  static const int kTextRepeatedFieldNumber = 2;
  inline const ::std::string& text_repeated(int index) const;
  inline ::std::string* mutable_text_repeated(int index);
  inline void set_text_repeated(int index, const ::std::string& value);
  inline void set_text_repeated(int index, const char* value);
  inline void set_text_repeated(int index, const char* value, size_t size);
  inline ::std::string* add_text_repeated();
  inline void add_text_repeated(const ::std::string& value);
  inline void add_text_repeated(const char* value);
  inline void add_text_repeated(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& text_repeated() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_text_repeated();
  
  // repeated .Foo.Bar bars = 3;
  inline int bars_size() const;
  inline void clear_bars();
  static const int kBarsFieldNumber = 3;
  inline const ::Foo_Bar& bars(int index) const;
  inline ::Foo_Bar* mutable_bars(int index);
  inline ::Foo_Bar* add_bars();
  inline const ::google::protobuf::RepeatedPtrField< ::Foo_Bar >&
      bars() const;
  inline ::google::protobuf::RepeatedPtrField< ::Foo_Bar >*
      mutable_bars();
  
  // @@protoc_insertion_point(class_scope:Foo)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* text_;
  static const ::std::string _default_text_;
  ::google::protobuf::RepeatedPtrField< ::std::string> text_repeated_;
  ::google::protobuf::RepeatedPtrField< ::Foo_Bar > bars_;
  friend void  protobuf_AddDesc_Foo_2eproto();
  friend void protobuf_AssignDesc_Foo_2eproto();
  friend void protobuf_ShutdownFile_Foo_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Foo* default_instance_;
};
// ===================================================================


// ===================================================================

// Foo_Bar

// required double dou = 1;
inline bool Foo_Bar::has_dou() const {
  return _has_bit(0);
}
inline void Foo_Bar::clear_dou() {
  dou_ = 0;
  _clear_bit(0);
}
inline double Foo_Bar::dou() const {
  return dou_;
}
inline void Foo_Bar::set_dou(double value) {
  _set_bit(0);
  dou_ = value;
}

// optional string text = 2;
inline bool Foo_Bar::has_text() const {
  return _has_bit(1);
}
inline void Foo_Bar::clear_text() {
  if (text_ != &_default_text_) {
    text_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& Foo_Bar::text() const {
  return *text_;
}
inline void Foo_Bar::set_text(const ::std::string& value) {
  _set_bit(1);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Foo_Bar::set_text(const char* value) {
  _set_bit(1);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Foo_Bar::set_text(const char* value, size_t size) {
  _set_bit(1);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  text_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Foo_Bar::mutable_text() {
  _set_bit(1);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  return text_;
}

// -------------------------------------------------------------------

// Foo

// optional string text = 1;
inline bool Foo::has_text() const {
  return _has_bit(0);
}
inline void Foo::clear_text() {
  if (text_ != &_default_text_) {
    text_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Foo::text() const {
  return *text_;
}
inline void Foo::set_text(const ::std::string& value) {
  _set_bit(0);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Foo::set_text(const char* value) {
  _set_bit(0);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  text_->assign(value);
}
inline void Foo::set_text(const char* value, size_t size) {
  _set_bit(0);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  text_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Foo::mutable_text() {
  _set_bit(0);
  if (text_ == &_default_text_) {
    text_ = new ::std::string;
  }
  return text_;
}

// repeated string text_repeated = 2;
inline int Foo::text_repeated_size() const {
  return text_repeated_.size();
}
inline void Foo::clear_text_repeated() {
  text_repeated_.Clear();
}
inline const ::std::string& Foo::text_repeated(int index) const {
  return text_repeated_.Get(index);
}
inline ::std::string* Foo::mutable_text_repeated(int index) {
  return text_repeated_.Mutable(index);
}
inline void Foo::set_text_repeated(int index, const ::std::string& value) {
  text_repeated_.Mutable(index)->assign(value);
}
inline void Foo::set_text_repeated(int index, const char* value) {
  text_repeated_.Mutable(index)->assign(value);
}
inline void Foo::set_text_repeated(int index, const char* value, size_t size) {
  text_repeated_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Foo::add_text_repeated() {
  return text_repeated_.Add();
}
inline void Foo::add_text_repeated(const ::std::string& value) {
  text_repeated_.Add()->assign(value);
}
inline void Foo::add_text_repeated(const char* value) {
  text_repeated_.Add()->assign(value);
}
inline void Foo::add_text_repeated(const char* value, size_t size) {
  text_repeated_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
Foo::text_repeated() const {
  return text_repeated_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
Foo::mutable_text_repeated() {
  return &text_repeated_;
}

// repeated .Foo.Bar bars = 3;
inline int Foo::bars_size() const {
  return bars_.size();
}
inline void Foo::clear_bars() {
  bars_.Clear();
}
inline const ::Foo_Bar& Foo::bars(int index) const {
  return bars_.Get(index);
}
inline ::Foo_Bar* Foo::mutable_bars(int index) {
  return bars_.Mutable(index);
}
inline ::Foo_Bar* Foo::add_bars() {
  return bars_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Foo_Bar >&
Foo::bars() const {
  return bars_;
}
inline ::google::protobuf::RepeatedPtrField< ::Foo_Bar >*
Foo::mutable_bars() {
  return &bars_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Foo_2eproto__INCLUDED
