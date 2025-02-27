# CppDSA

CppDSA is a deep dive into C++ data structures and algorithms, with a focus on exploring and benchmarking the components of the C++ Standard Library (STL). This project includes implementations, performance benchmarks, unit tests, profiling examples, and in-depth documentation—all built using modern C++20 and managed with CMake and Conan 2.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Directory Structure](#directory-structure)
- [Prerequisites](#prerequisites)
- [Installation and Setup](#installation-and-setup)
- [Building the Project](#building-the-project)
- [Running Unit Tests](#running-unit-tests)
- [Running Benchmarks](#running-benchmarks)
- [Generating Documentation](#generating-documentation)
- [Continuous Integration](#continuous-integration)
- [Contributing](#contributing)
- [License](#license)

## Overview

CppDSA is dedicated to exploring the intricacies of C++ data structures and algorithms. The project covers:
- **In-depth Documentation:** Detailed markdown guides and Doxygen-generated documentation on STL containers, iterators, algorithms, and advanced topics.
- **Performance Benchmarks:** Microbenchmarks using Google Benchmark to measure operations like insertion, deletion, and sorting across various STL containers.
- **Unit Testing:** A comprehensive suite of tests implemented with GoogleTest.
- **Profiling Examples:** Guidance and integration examples for profiling with tools such as gprof, Valgrind (Callgrind), and perf.
- **Modern C++:** Leveraging C++20 features and best practices.

## Features

- **Comprehensive STL Exploration:** Detailed study of containers (e.g., vector, list, deque, map, unordered_map), iterators, and algorithms.
- **Benchmarking and Profiling:** Real-world performance measurement and analysis.
- **Modular Build System:** Configured with CMake and managed via Conan 2.
- **Unit Tests:** Ensuring robustness and correctness of implementations.
- **Documentation:** Both in Markdown and auto-generated via Doxygen.
  
## Directory Structure

```
CppDSA/
├── cmake/                   # Additional CMake modules (e.g., doxygen configuration)
├── docs/                    # Markdown documentation and Doxygen configuration (Doxyfile)
├── include/                 # Header files
├── src/                     # Source code (benchmarks, data structure implementations, algorithms)
├── tests/                   # Unit tests (GoogleTest)
├── CMakeLists.txt           # Top-level CMake configuration
├── conanfile.txt            # Conan configuration for dependencies
├── CMakePresets.json        # CMake presets (including one for Conan 2)
└── LICENSE                  # Project license
```

## Prerequisites

- **Compiler:** A modern C++ compiler with C++20 support (GCC 10+, Clang 10+, or MSVC 2019+)
- **CMake:** Version 3.16 or later
- **Conan 2:** For dependency management
- **Python:** For installing Conan via pip (Python 3.x)
- **Optional Tools:**  
  - Valgrind, gprof, or perf for profiling  
  - Doxygen for generating HTML documentation

## Installation and Setup

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/MangaD/CppDSA.git
   cd CppDSA
   ```

2. **Install Conan 2 (if not already installed):**
   ```bash
   pipx ensurepath
   pipx install conan
   conan profile detect --force
   ```

3. **Conan Configuration:**
   Your `conanfile.txt` should include:
   ```ini
   [requires]
   gtest/1.12.1
   benchmark/1.6.1

   [generators]
   CMakeToolchain
   CMakeDeps
   ```
   This downloads and configures GoogleTest and Google Benchmark for your project.

## Building the Project

   ```bash
   mkdir -p build && cd build
   conan install .. --build=missing -of . -s build_type=RelWithDebInfo
   cmake .. --preset conan-relwithdebinfo
   cmake --build . --config RelWithDebInfo -- -j$(nproc)
   ```

## Running Unit Tests

Unit tests are located in the `tests/` directory and are built with GoogleTest. To run the tests:
```bash
cd build
ctest --output-on-failure
```
Alternatively, run the test executable directly:
```bash
./tests/unit_tests
```

## Running Benchmarks

Benchmark executables (using Google Benchmark) are built in the output directory. From the build directory, run:
```bash
./vector_benchmark
./map_benchmark
./unordered_map_benchmark
./deque_benchmark
```
Each executable measures the performance of various operations on different STL containers.

## Generating Documentation

Doxygen documentation can be generated with a dedicated CMake target. Once your build is configured:
```bash
cmake --build . --target doxygen
```
This command generates HTML documentation under `docs/doxygen/html/`. Open the `index.html` file in your browser to view the documentation.

## Continuous Integration

This project includes a GitHub Actions workflow (see `.github/workflows/ci.yml`) that:
- Checks out the repository.
- Installs system dependencies (cmake, g++, valgrind, etc.).
- Installs Conan via pip and caches the Conan 2 directory (`~/.conan2`) and build directory.
- Configures the project using CMake presets and the Conan toolchain file.
- Builds the project, runs unit tests, and executes benchmarks.

## Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Follow the coding guidelines and update tests/documentation as needed.
4. Submit a pull request for review.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
