// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#ifndef NEAPP_AVKON_CONFIG_HPP
#define NEAPP_AVKON_CONFIG_HPP

#include <boost/asio.hpp>
#include <boost/assert/source_location.hpp>

#ifndef _MSC_VER
#ifndef AVKON_EXPORT
#define AVKON_EXPORT __attribute__((visibility("default")))
#endif
#else
#ifndef AVKON_EXPORT
#define AVKON_EXPORT __declspec(dllexport)
#endif
#endif

#define NEAPP_AVKON_VERSION "v1.1.1-AVKON-PUBLIC"
#define NEAPP_AVKON_VERSION_BCD 0x1000000

namespace ne_app::core {

template <typename Pair>
struct storage_object;

template <typename Key, typename Data>
struct storage_pair;

using version_type = uint32_t;

using stream_type = std::stringstream;

}  // namespace ne_app::core

#endif