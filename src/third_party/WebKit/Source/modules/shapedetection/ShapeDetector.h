// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ShapeDetector_h
#define ShapeDetector_h

#include "bindings/core/v8/ScriptPromise.h"
#include "bindings/core/v8/ScriptPromiseResolver.h"
#include "core/imagebitmap/ImageBitmapFactories.h"
#include "modules/ModulesExport.h"
#include "modules/canvas2d/CanvasRenderingContext2D.h"

namespace blink {

class MODULES_EXPORT ShapeDetector
    : public GarbageCollectedFinalized<ShapeDetector> {
 public:
  virtual ~ShapeDetector() = default;

  ScriptPromise detect(ScriptState*, const ImageBitmapSourceUnion&);
  DEFINE_INLINE_VIRTUAL_TRACE() {}

 private:
  ScriptPromise DetectShapesOnImageData(ScriptPromiseResolver*, ImageData*);
  ScriptPromise DetectShapesOnImageElement(ScriptPromiseResolver*,
                                           const HTMLImageElement*);

  virtual ScriptPromise DoDetect(ScriptPromiseResolver*,
                                 mojo::ScopedSharedBufferHandle,
                                 int image_width,
                                 int image_height) = 0;
};

}  // namespace blink

#endif  // ShapeDetector_h
