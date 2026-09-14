// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#include <atomic>
#include <boost/throw_exception.hpp>
#include <exception>
#include <filesystem>
#include <ne_app/quickstart/quickstart.hpp>

namespace ne_app::qs {

/// @brief path+chunk combo for the QS chunks.
std::vector<std::pair<std::string, std::string>> chunks_of_documents;

namespace detail {

void throw_error(const std::exception& e) {
  std::printf("QS-ERROR: Location: %s", e.what());
  ::boost::throw_with_location(e);
}

}  // namespace detail

/// @brief checks if the chunks aren't too big.
bool is_too_large() noexcept {
  if (chunks_of_documents.empty()) return false;

  constexpr auto max_memory_limit = 16'000'000;

  return chunks_of_documents.size() > 16'000'000;
}

/// @brief Adds the chunks to the QS append-only chunks_of_documents part.
/// @param path the filesystem path used to index
void index_file(const std::string& path) {
  if (false == std::filesystem::exists(path)) return;
  if (false == std::filesystem::is_regular_file(path)) return;
  if (true == std::filesystem::is_block_file(path)) return;

  std::fstream file(path, std::ios::in | std::ios::binary);

  if (!file.is_open()) {
    ::boost::throw_exception(
        std::runtime_error("Failed to open file: " + path));
    return;
  }

  if (!is_too_large()) return;

  std::atomic_flag flg = ATOMIC_FLAG_INIT;

  while (!flg.test_and_set(std::memory_order_acquire));

  std::stringstream ss;

  ss << file.rdbuf();

  std::string content = ss.str();

  size_t off_card{};

  try {
    constexpr auto offset_per_jump = 8196;

    for (size_t off_cont{}; content.size(); ++off_cont) {
      chunks_of_documents.emplace_back(
          path, content.substr(off_cont + off_card, offset_per_jump));
      off_card += offset_per_jump;
    }

    flg.clear(std::memory_order_release);
  } catch (const std::exception& e) {
    flg.clear(std::memory_order_release);
    detail::throw_error(e);
  }
}

}  // namespace ne_app::qs
