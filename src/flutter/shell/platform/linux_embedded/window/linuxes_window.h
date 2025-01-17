// Copyright 2021 Sony Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_LINUX_EMBEDDED_WINDOW_LINUXES_WINDOW_H_
#define FLUTTER_SHELL_PLATFORM_LINUX_EMBEDDED_WINDOW_LINUXES_WINDOW_H_

#include "flutter/shell/platform/linux_embedded/public/flutter_linuxes.h"

namespace flutter {

class LinuxesWindow {
 public:
  LinuxesWindow() = default;
  virtual ~LinuxesWindow() = default;

 protected:
  virtual bool IsValid() const = 0;

  uint32_t GetCurrentWidth() const { return current_width_; }
  uint32_t GetCurrentHeight() const { return current_height_; }

  double current_scale_ = 1.0;

  int32_t current_width_ = -1;
  int32_t current_height_ = -1;

  bool show_cursor_;

  FlutterWindowMode window_mode_;

  double pointer_x_ = 0;
  double pointer_y_ = 0;

  std::string clipboard_data_ = "";
};

}  // namespace flutter

#endif  // FLUTTER_SHELL_PLATFORM_LINUX_EMBEDDED_WINDOW_LINUXES_WINDOW_H_
