// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#pragma once

#include <atomic>
#include <functional>
#include <future>

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
enum class await_or_error {
  kError = 588,
  kNoAwait = kError,
  kSuccess = 88,
};

/// @brief Await task first, then respond.
template <typename RetProm, typename Args, typename... Args2>
std::promise<RetProm> await_first(const std::function<Args>& fn, task_tag& t, Args2&&... a) {
  while (!t.tf_.test_and_set(std::memory_order_acquire));

  try {
    co_await fn(t.tf_, a...);
  } catch (...) {
    t.tf_.clear(std::memory_order_release);
    co_return RetProm::kError;
  }

  t.tf_.clear(std::memory_order_release);
  co_return RetProm::kSuccess;
}

}  // namespace ne_app::tasks
