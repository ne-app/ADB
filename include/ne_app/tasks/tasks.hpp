// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#pragma once

#include <atomic>
#include <functional>

namespace ne_app::tasks {

struct task_tag final {
  std::atomic_flag tf_{};
  task_tag() = default;
  ~task_tag() = default;
};

template <typename Args, typename... Args2>
void run(const std::function<Args>& fn, task_tag& t, Args2&&... a) {
  while (!t.tf_.test_and_set(std::memory_order_acquire));

  try {
    fn(t.tf_, a...);
  } catch (...) {
    t.tf_.clear(std::memory_order_release);
    return;
  }

  t.tf_.clear(std::memory_order_release);
}

/// @brief protocol definitions for 'await_or_error' type of return promises.
enum class await_or_error : int32_t {
  error = 588,
  success = 589,
};

/// @brief Await task first, then respond.
template <typename Args, typename... Args2>
await_or_error await_first(const std::function<Args>& fn, task_tag& t, Args2&&... a) {
  while (!t.tf_.test_and_set(std::memory_order_acquire));

  try {
    co_await fn(t.tf_, a...);
  } catch (...) {
    t.tf_.clear(std::memory_order_release);
    co_return await_or_error::error;
  }

  t.tf_.clear(std::memory_order_release);
  co_return await_or_error::success;
}

}  // namespace ne_app::tasks
