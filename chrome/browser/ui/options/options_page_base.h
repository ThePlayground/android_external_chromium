// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_OPTIONS_OPTIONS_PAGE_BASE_H_
#define CHROME_BROWSER_UI_OPTIONS_OPTIONS_PAGE_BASE_H_
#pragma once

#include <string>

#include "base/basictypes.h"
#include "chrome/browser/metrics/user_metrics.h"
#include "chrome/browser/ui/options/options_window.h"
#include "content/common/notification_observer.h"

class PrefService;
class Profile;
struct UserMetricsAction;

///////////////////////////////////////////////////////////////////////////////
// OptionsPageBase
//
//  A base class for Options dialog pages that handles observing preferences
//
class OptionsPageBase : public NotificationObserver {
 public:
  virtual ~OptionsPageBase();

  // Highlights the specified group to attract the user's attention.
  virtual void HighlightGroup(OptionsGroup highlight_group) { }

  // Overridden from NotificationObserver:
  virtual void Observe(NotificationType type,
                       const NotificationSource& source,
                       const NotificationDetails& details);

 protected:
  // This class cannot be instantiated directly, but its constructor must be
  // called by derived classes.
  explicit OptionsPageBase(Profile* profile);

  // Returns the Profile associated with this page.
  Profile* profile() const { return profile_; }

  // Records a user action and schedules the prefs file to be saved.
  void UserMetricsRecordAction(const UserMetricsAction &action,
                               PrefService* prefs);

  // Allows the UI to update when a preference value changes. The parameter is
  // the specific pref that changed, or NULL if all pref UI should be
  // validated. This should be called during setup, but with NULL as the
  // parameter to allow initial state to be set.
  virtual void NotifyPrefChanged(const std::string* pref_name) {}

 private:
  // The Profile associated with this page.
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(OptionsPageBase);
};

#endif  // CHROME_BROWSER_UI_OPTIONS_OPTIONS_PAGE_BASE_H_
