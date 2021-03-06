// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/sensor/Accelerometer.h"

using device::mojom::blink::SensorType;

namespace blink {

Accelerometer* Accelerometer::Create(ExecutionContext* execution_context,
                                     const SensorOptions& options,
                                     ExceptionState& exception_state) {
  return new Accelerometer(execution_context, options, exception_state);
}

// static
Accelerometer* Accelerometer::Create(ExecutionContext* execution_context,
                                     ExceptionState& exception_state) {
  return Create(execution_context, SensorOptions(), exception_state);
}

Accelerometer::Accelerometer(ExecutionContext* execution_context,
                             const SensorOptions& options,
                             ExceptionState& exception_state)
    : Sensor(execution_context,
             options,
             exception_state,
             SensorType::ACCELEROMETER) {}

double Accelerometer::x(bool& is_null) const {
  return ReadingValue(0, is_null);
}

double Accelerometer::y(bool& is_null) const {
  return ReadingValue(1, is_null);
}

double Accelerometer::z(bool& is_null) const {
  return ReadingValue(2, is_null);
}

DEFINE_TRACE(Accelerometer) {
  Sensor::Trace(visitor);
}

}  // namespace blink
