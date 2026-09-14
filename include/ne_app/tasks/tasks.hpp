// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#pragma once

#include <ne_app/core/core.hpp>

#include <atomic>

namespace ne_app::tasks {

struct task_tag final {
  std::atomic_flag tf_{};
  task_tag() = default;
  ~task_tag() = default;
};

}  // namespace ne_app::tasks

#include "tasks.inl"
