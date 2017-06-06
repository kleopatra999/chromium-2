// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/union_container.h.tmpl

// clang-format off
#ifndef ElementSequenceOrByteStringDoubleOrStringRecord_h
#define ElementSequenceOrByteStringDoubleOrStringRecord_h

#include "bindings/core/v8/Dictionary.h"
#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/NativeValueTraits.h"
#include "bindings/core/v8/V8Binding.h"
#include "core/CoreExport.h"
#include "platform/heap/Handle.h"

namespace blink {

class DoubleOrString;
class Element;

class CORE_EXPORT ElementSequenceOrByteStringDoubleOrStringRecord final {
  DISALLOW_NEW_EXCEPT_PLACEMENT_NEW();
 public:
  ElementSequenceOrByteStringDoubleOrStringRecord();
  bool isNull() const { return m_type == SpecificTypeNone; }

  bool isByteStringDoubleOrStringRecord() const { return m_type == SpecificTypeByteStringDoubleOrStringRecord; }
  const HeapVector<std::pair<String, DoubleOrString>>& getAsByteStringDoubleOrStringRecord() const;
  void setByteStringDoubleOrStringRecord(const HeapVector<std::pair<String, DoubleOrString>>&);
  static ElementSequenceOrByteStringDoubleOrStringRecord fromByteStringDoubleOrStringRecord(const HeapVector<std::pair<String, DoubleOrString>>&);

  bool isElementSequence() const { return m_type == SpecificTypeElementSequence; }
  const HeapVector<Member<Element>>& getAsElementSequence() const;
  void setElementSequence(const HeapVector<Member<Element>>&);
  static ElementSequenceOrByteStringDoubleOrStringRecord fromElementSequence(const HeapVector<Member<Element>>&);

  ElementSequenceOrByteStringDoubleOrStringRecord(const ElementSequenceOrByteStringDoubleOrStringRecord&);
  ~ElementSequenceOrByteStringDoubleOrStringRecord();
  ElementSequenceOrByteStringDoubleOrStringRecord& operator=(const ElementSequenceOrByteStringDoubleOrStringRecord&);
  DECLARE_TRACE();

 private:
  enum SpecificTypes {
    SpecificTypeNone,
    SpecificTypeByteStringDoubleOrStringRecord,
    SpecificTypeElementSequence,
  };
  SpecificTypes m_type;

  HeapVector<std::pair<String, DoubleOrString>> m_byteStringDoubleOrStringRecord;
  HeapVector<Member<Element>> m_elementSequence;

  friend CORE_EXPORT v8::Local<v8::Value> ToV8(const ElementSequenceOrByteStringDoubleOrStringRecord&, v8::Local<v8::Object>, v8::Isolate*);
};

class V8ElementSequenceOrByteStringDoubleOrStringRecord final {
 public:
  CORE_EXPORT static void toImpl(v8::Isolate*, v8::Local<v8::Value>, ElementSequenceOrByteStringDoubleOrStringRecord&, UnionTypeConversionMode, ExceptionState&);
};

CORE_EXPORT v8::Local<v8::Value> ToV8(const ElementSequenceOrByteStringDoubleOrStringRecord&, v8::Local<v8::Object>, v8::Isolate*);

template <class CallbackInfo>
inline void V8SetReturnValue(const CallbackInfo& callbackInfo, ElementSequenceOrByteStringDoubleOrStringRecord& impl) {
  V8SetReturnValue(callbackInfo, ToV8(impl, callbackInfo.Holder(), callbackInfo.GetIsolate()));
}

template <class CallbackInfo>
inline void V8SetReturnValue(const CallbackInfo& callbackInfo, ElementSequenceOrByteStringDoubleOrStringRecord& impl, v8::Local<v8::Object> creationContext) {
  V8SetReturnValue(callbackInfo, ToV8(impl, creationContext, callbackInfo.GetIsolate()));
}

template <>
struct NativeValueTraits<ElementSequenceOrByteStringDoubleOrStringRecord> : public NativeValueTraitsBase<ElementSequenceOrByteStringDoubleOrStringRecord> {
  CORE_EXPORT static ElementSequenceOrByteStringDoubleOrStringRecord NativeValue(v8::Isolate*, v8::Local<v8::Value>, ExceptionState&);
};

template <>
struct V8TypeOf<ElementSequenceOrByteStringDoubleOrStringRecord> {
  typedef V8ElementSequenceOrByteStringDoubleOrStringRecord Type;
};

}  // namespace blink

// We need to set canInitializeWithMemset=true because HeapVector supports
// items that can initialize with memset or have a vtable. It is safe to
// set canInitializeWithMemset=true for a union type object in practice.
// See https://codereview.chromium.org/1118993002/#msg5 for more details.
WTF_ALLOW_MOVE_AND_INIT_WITH_MEM_FUNCTIONS(blink::ElementSequenceOrByteStringDoubleOrStringRecord);

#endif  // ElementSequenceOrByteStringDoubleOrStringRecord_h