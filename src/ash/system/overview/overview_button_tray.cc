// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/system/overview/overview_button_tray.h"

#include "ash/resources/vector_icons/vector_icons.h"
#include "ash/session/session_controller.h"
#include "ash/shelf/shelf_constants.h"
#include "ash/shell.h"
#include "ash/shell_port.h"
#include "ash/strings/grit/ash_strings.h"
#include "ash/system/tray/system_tray_delegate.h"
#include "ash/system/tray/tray_constants.h"
#include "ash/wm/maximize_mode/maximize_mode_controller.h"
#include "ash/wm/overview/window_selector_controller.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/gfx/paint_vector_icon.h"
#include "ui/views/border.h"
#include "ui/views/controls/image_view.h"

namespace ash {

OverviewButtonTray::OverviewButtonTray(WmShelf* wm_shelf)
    : TrayBackgroundView(wm_shelf, true), icon_(new views::ImageView()) {
  SetInkDropMode(InkDropMode::ON);

  icon_->SetImage(CreateVectorIcon(kShelfOverviewIcon, kShelfIconColor));
  SetIconBorderForShelfAlignment();
  tray_container()->AddChildView(icon_);

  // Since OverviewButtonTray is located on the rightmost position of a
  // horizontal shelf, no separator is required.
  set_separator_visibility(false);

  Shell::Get()->AddShellObserver(this);
  Shell::Get()->session_controller()->AddSessionStateObserver(this);
}

OverviewButtonTray::~OverviewButtonTray() {
  Shell::Get()->RemoveShellObserver(this);
  Shell::Get()->session_controller()->RemoveSessionStateObserver(this);
}

void OverviewButtonTray::UpdateAfterLoginStatusChange(LoginStatus status) {
  UpdateIconVisibility();
}

bool OverviewButtonTray::PerformAction(const ui::Event& event) {
  WindowSelectorController* controller =
      Shell::Get()->window_selector_controller();
  // Toggling overview mode will fail if there is no window to show.
  bool performed = controller->ToggleOverview();
  ShellPort::Get()->RecordUserMetricsAction(UMA_TRAY_OVERVIEW);
  return performed;
}

void OverviewButtonTray::SessionStateChanged(
    session_manager::SessionState state) {
  UpdateIconVisibility();
}

void OverviewButtonTray::OnMaximizeModeStarted() {
  UpdateIconVisibility();
}

void OverviewButtonTray::OnMaximizeModeEnded() {
  UpdateIconVisibility();
}

void OverviewButtonTray::OnOverviewModeStarting() {
  SetIsActive(true);
}

void OverviewButtonTray::OnOverviewModeEnded() {
  SetIsActive(false);
}

void OverviewButtonTray::ClickedOutsideBubble() {}

base::string16 OverviewButtonTray::GetAccessibleNameForTray() {
  return l10n_util::GetStringUTF16(IDS_ASH_OVERVIEW_BUTTON_ACCESSIBLE_NAME);
}

void OverviewButtonTray::HideBubbleWithView(
    const views::TrayBubbleView* bubble_view) {
  // This class has no bubbles to hide.
}

void OverviewButtonTray::SetShelfAlignment(ShelfAlignment alignment) {
  if (alignment == shelf_alignment())
    return;

  TrayBackgroundView::SetShelfAlignment(alignment);
  SetIconBorderForShelfAlignment();
}

void OverviewButtonTray::SetIconBorderForShelfAlignment() {
  // Pad button size to align with other controls in the system tray.
  const gfx::ImageSkia& image = icon_->GetImage();
  const int vertical_padding = (kTrayItemSize - image.height()) / 2;
  const int horizontal_padding = (kTrayItemSize - image.width()) / 2;
  icon_->SetBorder(views::CreateEmptyBorder(
      gfx::Insets(vertical_padding, horizontal_padding)));
}

void OverviewButtonTray::UpdateIconVisibility() {
  // The visibility of the OverviewButtonTray has diverged from
  // WindowSelectorController::CanSelect. The visibility of the button should
  // not change during transient times in which CanSelect is false. Such as when
  // a modal dialog is present.
  SessionController* session_controller = Shell::Get()->session_controller();

  Shell* shell = Shell::Get();
  SetVisible(
      shell->maximize_mode_controller()->IsMaximizeModeWindowManagerEnabled() &&
      session_controller->IsActiveUserSessionStarted() &&
      !session_controller->IsScreenLocked() &&
      session_controller->GetSessionState() ==
          session_manager::SessionState::ACTIVE &&
      shell->system_tray_delegate()->GetUserLoginStatus() !=
          LoginStatus::KIOSK_APP &&
      shell->system_tray_delegate()->GetUserLoginStatus() !=
          LoginStatus::ARC_KIOSK_APP);
}

}  // namespace ash