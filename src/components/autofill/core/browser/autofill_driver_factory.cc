// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/autofill/core/browser/autofill_driver_factory.h"

#include "base/callback.h"
#include "components/autofill/core/browser/autofill_client.h"
#include "components/autofill/core/browser/autofill_driver.h"

namespace autofill {

AutofillDriverFactory::AutofillDriverFactory(AutofillClient* client)
    : client_(client) {}

AutofillDriverFactory::~AutofillDriverFactory() {}

AutofillDriver* AutofillDriverFactory::DriverForKey(void* key) {
  auto mapping = driver_map_.find(key);
  return mapping == driver_map_.end() ? nullptr : mapping->second.get();
}

void AutofillDriverFactory::NavigationFinished() {
  user_gesture_seen_ = false;
  client_->HideAutofillPopup();
}

void AutofillDriverFactory::TabHidden() {
  client_->HideAutofillPopup();
}

void AutofillDriverFactory::OnFirstUserGestureObserved() {
  if (user_gesture_seen_)
    return;

  for (auto& driver : driver_map_)
    driver.second->NotifyFirstUserGestureObservedInTab();

  user_gesture_seen_ = true;
}

void AutofillDriverFactory::AddForKey(
    void* key,
    base::Callback<std::unique_ptr<AutofillDriver>()> factory_method) {
  auto insertion_result = driver_map_.insert(std::make_pair(key, nullptr));
  // This can be called twice for the key representing the main frame.
  if (insertion_result.second) {
    insertion_result.first->second = factory_method.Run();
    if (user_gesture_seen_)
      insertion_result.first->second->NotifyFirstUserGestureObservedInTab();
  }
}

void AutofillDriverFactory::DeleteForKey(void* key) {
  driver_map_.erase(key);
}

}  // namespace autofill