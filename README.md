# AVKON SDK

The AVKON SDK is a C++23 shared library by [Ne.app](https://ne-app.eu) that provides PDF viewing, HTML/web rendering, file indexing, and store management for Ne.app applications.

**Repository:** https://github.com/ne-app/adb  
**License:** Apache-2.0  
**Author:** Amlal El Mahrouss <amlal@ne-app.eu>

---

## Features

- PDF viewer (`ne_app::pdf`)
- HTML/WebKit viewer (`ne_app::www`)
- File indexer (`ne_app::qs`)
- App store integration (`ne_app::store`)
- Task scheduling (`ne_app::tasks`)

## Requirements

| Dependency | Notes |
|---|---|
| CMake ≥ 3.25.1 | Build system |
| C++23 compiler | GCC 13+ or Clang 16+ |
| Boost | General utilities |
| TBB | Parallel execution |
| GTK4 | UI backend (Linux) |
| WebKit2GTK 4.1 | HTML rendering (Linux) |
| JavaScriptCore GTK 4.1 | JS engine (Linux) |

## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

To install headers and the shared library:

```sh
cmake -B build -DNEAPP_INSTALL_AVKON=1
cmake --install build
```

## Usage

```cpp
#include <ne_app/quickstart/quickstart.hpp>

// Index a file for quickstart
ne_app::qs::index_file("/path/to/file");

// Check size limit before indexing
if (!ne_app::qs::is_too_large()) {
    ne_app::qs::index_file("/path/to/file");
}
```

## Project Layout

```
include/ne_app/     Public headers
src/ne_app/         Implementation
example/            Usage examples
test/               Test suite
benchmark/          Benchmarks
```
