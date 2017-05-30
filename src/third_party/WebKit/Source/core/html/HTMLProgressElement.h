/*
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef HTMLProgressElement_h
#define HTMLProgressElement_h

#include "core/CoreExport.h"
#include "core/html/LabelableElement.h"

namespace blink {

class LayoutProgress;

class CORE_EXPORT HTMLProgressElement final : public LabelableElement {
  DEFINE_WRAPPERTYPEINFO();

 public:
  static const double IndeterminatePosition;
  static const double InvalidPosition;

  static HTMLProgressElement* create(Document&);

  double value() const;
  void setValue(double);

  double max() const;
  void setMax(double);

  double position() const;

  bool canContainRangeEndPoint() const override { return false; }

  DECLARE_VIRTUAL_TRACE();

 private:
  explicit HTMLProgressElement(Document&);
  ~HTMLProgressElement() override;

  bool areAuthorShadowsAllowed() const override { return false; }
  bool shouldAppearIndeterminate() const override;
  bool supportLabels() const override { return true; }

  LayoutObject* createLayoutObject(const ComputedStyle&) override;
  LayoutProgress* layoutProgress() const;

  void parseAttribute(const AttributeModificationParams&) override;

  void attachLayoutTree(const AttachContext& = AttachContext()) override;

  void didElementStateChange();
  void didAddUserAgentShadowRoot(ShadowRoot&) override;
  bool isDeterminate() const;
  void setValueWidthPercentage(double) const;

  Member<Element> m_value;
};

}  // namespace blink

#endif  // HTMLProgressElement_h