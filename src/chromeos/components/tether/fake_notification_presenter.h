// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_COMPONENTS_TETHER_FAKE_NOTIFICATION_PRESENTER_H_
#define CHROMEOS_COMPONENTS_TETHER_FAKE_NOTIFICATION_PRESENTER_H_

#include <memory>
#include <string>

#include "base/macros.h"
#include "chromeos/components/tether/notification_presenter.h"

namespace chromeos {

namespace tether {

class FakeNotificationPresenter : public NotificationPresenter {
 public:
  enum class PotentialHotspotNotificationState {
    SINGLE_HOTSPOT_NEARBY_SHOWN,
    MULTIPLE_HOTSPOTS_NEARBY_SHOWN,
    NO_HOTSPOT_NOTIFICATION_SHOWN
  };

  FakeNotificationPresenter();
  ~FakeNotificationPresenter() override;

  PotentialHotspotNotificationState potential_hotspot_state() {
    return potential_hotspot_state_;
  }

  // Note: This function fails a test if potential_hotspot_state() is not
  // SINGLE_HOTSPOT_NEARBY_SHOWN when called.
  cryptauth::RemoteDevice& GetPotentialHotspotRemoteDevice();

  bool is_connection_failed_notification_shown() {
    return is_connection_failed_notification_shown_;
  }

  // NotificationPresenter:
  void NotifyPotentialHotspotNearby(
      const cryptauth::RemoteDevice& remote_device) override;
  void NotifyMultiplePotentialHotspotsNearby() override;
  void RemovePotentialHotspotNotification() override;
  void NotifyConnectionToHostFailed() override;
  void RemoveConnectionToHostFailedNotification() override;

 private:
  PotentialHotspotNotificationState potential_hotspot_state_;
  cryptauth::RemoteDevice potential_hotspot_remote_device_;
  bool is_connection_failed_notification_shown_;

  DISALLOW_COPY_AND_ASSIGN(FakeNotificationPresenter);
};

}  // namespace tether

}  // namespace chromeos

#endif  // CHROMEOS_COMPONENTS_TETHER_FAKE_NOTIFICATION_PRESENTER_H_