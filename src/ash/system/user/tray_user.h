// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_USER_TRAY_USER_H_
#define ASH_SYSTEM_USER_TRAY_USER_H_

#include "ash/ash_export.h"
#include "ash/public/cpp/session_types.h"
#include "ash/session/session_state_observer.h"
#include "ash/system/tray/system_tray_item.h"
#include "base/macros.h"

namespace gfx {
class Rect;
class Size;
}

namespace views {
class Label;
}

namespace ash {

namespace tray {
class RoundedImageView;
class UserView;
}

class ASH_EXPORT TrayUser : public SystemTrayItem, public SessionStateObserver {
 public:
  // The given |index| is the user index in a multi profile scenario. Index #0
  // is the active user, the other indices are other logged in users (if there
  // are any). Depending on the multi user mode, there will be either one (index
  // #0) or all users be visible in the system tray.
  TrayUser(SystemTray* system_tray, UserIndex index);
  ~TrayUser() override;

  // Allows unit tests to see if the item was created.
  enum TestState {
    HIDDEN,              // The item is hidden.
    SHOWN,               // The item gets presented to the user.
    HOVERED,             // The item is hovered and presented to the user.
    ACTIVE,              // The item was clicked and can add a user.
    ACTIVE_BUT_DISABLED  // The item was clicked anc cannot add a user.
  };
  TestState GetStateForTest() const;

  // Returns the size of layout_view_.
  gfx::Size GetLayoutSizeForTest() const;

  // Returns the bounds of the user panel in screen coordinates.
  // Note: This only works when the panel shown.
  gfx::Rect GetUserPanelBoundsInScreenForTest() const;

  // Update the TrayUser as if the current LoginStatus is |status|.
  void UpdateAfterLoginStatusChangeForTest(LoginStatus status);

  // Use for access inside of tests.
  tray::UserView* user_view_for_test() const { return user_; }
  tray::RoundedImageView* avatar_view_for_test() const { return avatar_; }

 private:
  // Overridden from SystemTrayItem.
  views::View* CreateTrayView(LoginStatus status) override;
  views::View* CreateDefaultView(LoginStatus status) override;
  void DestroyTrayView() override;
  void DestroyDefaultView() override;
  void UpdateAfterLoginStatusChange(LoginStatus status) override;
  void UpdateAfterShelfAlignmentChange(ShelfAlignment alignment) override;

  // Overridden from SessionStateObserver.
  void ActiveUserChanged(const AccountId& account_id) override;
  void UserAddedToSession(const AccountId& account_id) override;
  void UserSessionUpdated(const AccountId& account_id) override;

  void UpdateAvatarImage(LoginStatus status);

  // Updates the layout of this item.
  void UpdateLayoutOfItem();

  ScopedSessionStateObserver scoped_session_observer_;

  // The user index to use.
  const UserIndex user_index_;

  tray::UserView* user_ = nullptr;

  // View that contains label and/or avatar.
  views::View* layout_view_ = nullptr;
  tray::RoundedImageView* avatar_ = nullptr;
  views::Label* label_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(TrayUser);
};

}  // namespace ash

#endif  // ASH_SYSTEM_USER_TRAY_USER_H_