// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#pragma once

#include <ne_app/core/core.hpp>
#include <ne_app/core/store.hpp>
#include <ne_app/www/httplib.hpp>

namespace ne_app::qs {

bool AVKON_EXPORT is_too_large() noexcept;
void AVKON_EXPORT index_file(const std::string& path);

}  // namespace ne_app::qs
