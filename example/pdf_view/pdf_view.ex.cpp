// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#include <ne_app/core/pdf.hpp>
#include <ne_app/tasks/tasks.hpp>

ne_app::tasks::task_coroutine task(int argc, char** argv) {
  if (argc < 2) co_return;

  try {
    ne_app::tasks::task_tag t;

    ne_app::tasks::run<void(std::atomic_flag&)>([&argv](std::atomic_flag& fl) { 
      ::ne_app::pdf::render(argv[1], ::strlen(argv[1]));
      fl.clear(std::memory_order_release);
    }, t);

    co_return;
  } catch (...) {
    co_return;
  }
}

int main(int argc, char** argv) {
  auto t = task(argc, argv);
  t.resume();
  //t.destroy();
}
