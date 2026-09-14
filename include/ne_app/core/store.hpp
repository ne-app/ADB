// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#ifndef NEAPP_AVKON_CORE_HPP
#define NEAPP_AVKON_CORE_HPP

#include <ne_app/core/detail/config.hpp>
#include <string>

namespace ne_app::core {

void throw_pdf_error(
    const boost::source_location& src = BOOST_CURRENT_LOCATION);

template <typename KeyType, typename ValueType>
struct storage_pair {
  using key_type = KeyType;
  using value_type = ValueType;
};

template <typename Pair>
struct storage_object final : public Pair {
  using key_type = typename Pair::key_type;
  using value_type = typename Pair::value_type;

  key_type key_;
  value_type value_;
};

}  // namespace ne_app::core

#endif  // ifndef NEAPP_AVKON_CORE_HPP
