// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CSSRotation_h
#define CSSRotation_h

#include "core/css/cssom/CSSAngleValue.h"
#include "core/css/cssom/CSSMatrixComponent.h"
#include "core/css/cssom/CSSTransformComponent.h"

namespace blink {

class CORE_EXPORT CSSRotation final : public CSSTransformComponent {
  WTF_MAKE_NONCOPYABLE(CSSRotation);
  DEFINE_WRAPPERTYPEINFO();

 public:
  static CSSRotation* Create(const CSSAngleValue* angle_value) {
    return new CSSRotation(angle_value);
  }

  static CSSRotation* Create(double x,
                             double y,
                             double z,
                             const CSSAngleValue* angle_value) {
    return new CSSRotation(x, y, z, angle_value);
  }

  static CSSRotation* FromCSSValue(const CSSFunctionValue&);

  // Bindings requires returning non-const pointers. This is safe because
  // CSSAngleValues are immutable.
  CSSAngleValue* angle() const {
    return const_cast<CSSAngleValue*>(angle_.Get());
  }
  double x() const { return x_; }
  double y() const { return y_; }
  double z() const { return z_; }

  TransformComponentType GetType() const override {
    return is2d_ ? kRotationType : kRotation3DType;
  }

  CSSMatrixComponent* asMatrix() const override {
    return is2d_ ? CSSMatrixComponent::Rotate(angle_->degrees())
                 : CSSMatrixComponent::Rotate3d(angle_->degrees(), x_, y_, z_);
  }

  CSSFunctionValue* ToCSSValue() const override;

  DEFINE_INLINE_VIRTUAL_TRACE() {
    visitor->Trace(angle_);
    CSSTransformComponent::Trace(visitor);
  }

 private:
  CSSRotation(const CSSAngleValue* angle)
      : angle_(angle), x_(0), y_(0), z_(1), is2d_(true) {}

  CSSRotation(double x, double y, double z, const CSSAngleValue* angle)
      : angle_(angle), x_(x), y_(y), z_(z), is2d_(false) {}

  Member<const CSSAngleValue> angle_;
  double x_;
  double y_;
  double z_;
  bool is2d_;
};

}  // namespace blink

#endif
