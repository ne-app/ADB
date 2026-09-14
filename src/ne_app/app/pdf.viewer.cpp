// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#ifdef __linux__
#define WEBVIEW_GTK
#endif

#ifdef _WIN32
#define WEBVIEW_WIN
#endif

#ifdef __APPLE__
#define WEBVIEW_MAC
#endif

#define WEBVIEW_IMPLEMENTATION

#include <ne_app/www/webview.hpp>
#include <ne_app/core/pdf.hpp>

#include <fstream>

static constexpr auto kViewName = "AVKON - PDF Viewer";

int ::ne_app::pdf::render(const char* path, const size_t len, bool debug) {
  if (!len) return EXIT_FAILURE;

  static_assert(std::is_same_v<decltype(path), std::nullptr_t> == false, "path is nullptr_t.");

  try {
    webview::webview w(debug, nullptr);
    
    w.set_title(kViewName);
    w.set_size(1280, 720, WEBVIEW_HINT_NONE);

    ne_app::core::stream_type ss;
    
    std::ifstream fs(path ? path : "");

    if (fs.good()) {
      ss << fs.rdbuf();
      w.set_pdf(ss);
    }

    w.run();
  } catch (...) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
