// Copyright 2021 Sony Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <flutter/dart_project.h>
#include <flutter/flutter_view_controller.h>

#include <iostream>
#include <memory>
#include <string>

#include "command_options.h"
#include "flutter_window.h"

int main(int argc, char** argv) {
  commandline::CommandOptions options;
  options.AddString("bundle", "b", "Path to Flutter app bundle", "./bundle",
                    true);
  options.AddWithoutValue("fullscreen", "f", "Always full-screen display",
                          false);
  options.AddWithoutValue("no-cursor", "n", "No mouse cursor/pointer", false);
  options.AddInt("width", "w", "Flutter app window width", 1280, false);
  options.AddInt("height", "h", "Flutter app window height", 720, false);
  if (!options.Parse(argc, argv)) {
    std::cerr << options.GetError() << std::endl;
    std::cout << options.ShowHelp();
    return 0;
  }

  // The project to run.
  const bool show_cursor = !options.Exist("no-cursor");
  const auto view_mode =
      options.Exist("fullscreen")
          ? flutter::FlutterViewController::ViewMode::kFullscreen
          : flutter::FlutterViewController::ViewMode::kNormal;
  const auto width = options.GetValue<int>("width");
  const auto height = options.GetValue<int>("height");
  const auto bundle_path = options.GetValue<std::string>("bundle");

  const std::wstring fl_path(bundle_path.begin(), bundle_path.end());
  flutter::DartProject project(fl_path);
  auto command_line_arguments = std::vector<std::string>();
  project.set_dart_entrypoint_arguments(std::move(command_line_arguments));

  // The Flutter instance hosted by this window.
  FlutterWindow window(project);
  if (!window.OnCreate(view_mode, width, height, show_cursor)) {
    std::cerr << "Failed to create a Flutter window." << std::endl;
    return 0;
  }
  window.Run();
  window.OnDestroy();
  return 0;
}
