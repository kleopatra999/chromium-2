/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2001 Peter Kelly (pmk@post.com)
 *           (C) 2001 Dirk Mueller (mueller@kde.org)
 * Copyright (C) 2003, 2004, 2005, 2006, 2008, 2010, 2013 Apple Inc. All rights
 * reserved.
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

#ifndef NamedNodeMap_h
#define NamedNodeMap_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "core/dom/Element.h"
#include "platform/wtf/text/AtomicString.h"

namespace blink {

class Attr;
class ExceptionState;

class NamedNodeMap final : public GarbageCollected<NamedNodeMap>,
                           public ScriptWrappable {
  DEFINE_WRAPPERTYPEINFO();
  friend class Element;

 public:
  static NamedNodeMap* Create(Element* element) {
    return new NamedNodeMap(element);
  }

  // Public DOM interface.

  Attr* getNamedItem(const AtomicString&) const;
  Attr* removeNamedItem(const AtomicString& name, ExceptionState&);

  Attr* getNamedItemNS(const AtomicString& namespace_uri,
                       const AtomicString& local_name) const;
  Attr* removeNamedItemNS(const AtomicString& namespace_uri,
                          const AtomicString& local_name,
                          ExceptionState&);

  Attr* setNamedItem(Attr*, ExceptionState&);
  Attr* setNamedItemNS(Attr*, ExceptionState&);

  Attr* item(unsigned index) const;
  size_t length() const;

  DECLARE_TRACE();

 private:
  explicit NamedNodeMap(Element* element) : element_(element) {
    // Only supports NamedNodeMaps with Element associated.
    DCHECK(element_);
  }

  Member<Element> element_;
};

}  // namespace blink

#endif  // NamedNodeMap_h
