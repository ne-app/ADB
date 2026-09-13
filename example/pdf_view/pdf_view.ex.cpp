// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#include <atomic>
#include <ne_app/core/pdf.hpp>
#include <ne_app/tasks/tasks.hpp>

int main(int argc, char** argv) {
  if (argc < 2) return EXIT_FAILURE;

  try {
    ne_app::tasks::task_tag t;

    ne_app::tasks::await_first<void(std::atomic_flag&)>([&argv](std::atomic_flag& fl) { 
      ::ne_app::pdf::render(argv[1], ::strlen(argv[1]));
      fl.clear(std::memory_order_release);
    }, t);

    return EXIT_SUCCESS;
  } catch (...) {
    return EXIT_FAILURE;
  }
}