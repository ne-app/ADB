// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#pragma once

#include <ne_app/core/store.hpp>
#include <ne_app/www/httplib.hpp>
#include <stdexcept>

/// @brief Namespace of Ne.app's QS Cache specs.
namespace ne_app::qs::detail {

/// @brief File frame from host configuration file to download for client file.
struct qs_info_frm final {
  int32_t magic_;
  int16_t type_;
  size_t len_;
  uint8_t pad_[4];
};

/// @brief File type of QS Cache.
enum : int16_t {
  kQSFileInvalid,
  kQSFilePDF = 700,
  kQSFileJSON,
  kQSFileJS,
  kQSFileHTML,
  kQSFileConfig,
};

/// @brief File magic number of QS Cache.
enum : int32_t {
  kQSMagicFilePDF = 0x874f8d,
  kQSMagicFileJSON,
  kQSMagicFileHTML,
  kQSMagicFileJS,
};

/// @brief Convert file type to string.
inline const char* qs_file_type_to_str(int16_t type) {
  switch (type) {
    case kQSFilePDF:
      return "PDF";
    case kQSFileJSON:
      return "JSON";
    case kQSFileJS:
      return "JS";
    case kQSFileHTML:
      return "HTML";
    case kQSFileConfig:
      return "CONFIG";
    default:
      return "INVALID";
  }
}

/// @brief Convert file magic number to string.
inline const char* qs_file_magic_to_str(int32_t magic) {
  switch (magic) {
    case kQSMagicFilePDF:
      return "PDF";
    case kQSMagicFileJSON:
      return "JSON";
    case kQSMagicFileHTML:
      return "HTML";
    case kQSMagicFileJS:
      return "JS";
    default:
      return "INVALID";
  }
}

using qs_exception = std::runtime_error;

struct qs_tag final {
  uint64_t id_{0};
};

}  // namespace ne_app::qs::detail

namespace ne_app::qs {

  bool is_too_large() noexcept;
void index_file(const std::string& path);

}  // namespace ne_app::qs
