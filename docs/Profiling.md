# Profiling Tools and Techniques for C++ Projects

This guide provides a deep dive into several popular profiling tools and techniques used to analyze and optimize C++ code. It covers **gprof**, **Valgrind (Callgrind)**, and **perf**. Additionally, it discusses how to prepare your builds for profiling, the differences between debug and release modes, and considerations for integrating profiling/benchmarking data into CI/CD pipelines.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Preparing Your Code for Profiling](#preparing-your-code-for-profiling)
3. [Profiling with gprof](#profiling-with-gprof)
   - [What is gprof?](#what-is-gprof)
   - [Setup and Usage](#setup-and-usage)
4. [Profiling with Valgrind (Callgrind)](#profiling-with-valgrind-callgrind)
   - [What is Valgrind/Callgrind?](#what-is-valgrindcallgrind)
   - [Setup and Usage](#setup-and-usage-1)
   - [Analyzing Results with KCachegrind](#analyzing-results-with-kcachegrind)
5. [Profiling with perf (Linux)](#profiling-with-perf-linux)
   - [What is perf?](#what-is-perf)
   - [Setup and Usage](#setup-and-usage-2)
6. [Debug vs. Release Builds](#debug-vs-release-builds)
7. [Integrating Profiling and Benchmarking in CI/CD](#integrating-profiling-and-benchmarking-in-cicd)
8. [Conclusion](#conclusion)

---

## Introduction

Profiling is an essential practice for understanding where your program spends its time and identifying performance bottlenecks. Unlike code coverage—which is often reported via services like Codecov or Coveralls—profiling typically requires collecting raw performance data that is then analyzed with specialized tools. Each tool provides different insights:

- **gprof**: Generates a flat profile and call graph by instrumenting the code (requires `-pg`).
- **Valgrind (Callgrind)**: Provides detailed call graphs and metrics on function call counts and execution paths.
- **perf**: Offers a wide range of profiling options on Linux, including sampling-based performance data and live views with `perf top`.

---

## Preparing Your Code for Profiling

Before profiling, you need to prepare your build:
- **Release Mode**: Always profile optimized (release mode) builds. This ensures that the performance data reflects real-world usage, as compiler optimizations (like inlining and loop unrolling) are enabled.
- **Profiling Flags**:
  - For **gprof**, compile and link with `-pg`. This instruments your code to produce a `gmon.out` file at runtime.
  - Tools like **Valgrind** and **perf** do not require special compiler flags, but ensure that debug symbols (using `-g`) are available for more meaningful analysis.

---

## Profiling with gprof

### What is gprof?

**gprof** is a GNU profiler that collects performance data by instrumenting your executable. It provides:
- A **flat profile**: Time spent in each function.
- A **call graph**: Who calls whom and how often.

### Setup and Usage

1. **Compile with `-pg`**:
   - Modify your CMake configuration (or build system) to add `-pg` to both compile and link flags:
     ```cmake
     set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pg")
     set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -pg")
     ```
2. **Build in Release Mode**:
   - Ensure you are using a release build to get realistic performance data:
     ```bash
     cmake .. -DCMAKE_BUILD_TYPE=Release
     make -j$(nproc)
     ```
3. **Run the Executable**:
   - Run your target (e.g., `./vector_benchmark`). This generates a `gmon.out` file.
4. **Analyze with gprof**:
   - Run:
     ```bash
     gprof ./vector_benchmark gmon.out > profile.txt
     ```
   - Open `profile.txt` to review the detailed profiling report.

---

## Profiling with Valgrind (Callgrind)

### What is Valgrind/Callgrind?

**Valgrind** is a powerful instrumentation framework that includes the **Callgrind** tool, which is used for profiling. It provides:
- Detailed call graphs.
- Metrics on function call counts and instruction counts.

### Setup and Usage

1. **Run under Callgrind**:
   - Execute your program with Callgrind:
     ```bash
     valgrind --tool=callgrind ./vector_benchmark
     ```
   - This produces an output file (e.g., `callgrind.out.<pid>`).

2. **Analyze Output**:
   - Use command-line tools:
     ```bash
     callgrind_annotate callgrind.out.<pid>
     ```
   - Or, for a graphical interface, see the next section.

### Analyzing Results with KCachegrind

- **KCachegrind**: A graphical viewer for Callgrind data.
  - Install KCachegrind (or QCachegrind on some distributions).
  - Open the output file:
    ```bash
    kcachegrind callgrind.out.<pid>
    ```
  - Explore the call graph, identify hotspots, and analyze the call paths.

---

## Profiling with perf (Linux)

### What is perf?

**perf** is a Linux profiling tool that uses sampling-based techniques. It provides:
- A **flat profile**.
- **Call graphs**.
- Live monitoring (via `perf top`).

### Setup and Usage

1. **Record Performance Data**:
   - Run your executable with perf:
     ```bash
     perf record -g ./vector_benchmark
     ```
   - This collects data and creates a `perf.data` file.

2. **Analyze the Data**:
   - Use:
     ```bash
     perf report
     ```
   - This opens an interactive interface where you can navigate through function calls and hotspots.

3. **Live Profiling**:
   - Run:
     ```bash
     perf top
     ```
   - This command shows real-time profiling data similar to the Unix `top` command.

### Installing perf on WSL2

Install dependencies (more may be needed):
```sh
sudo apt update && sudo apt install build-essential flex bison libssl-dev libelf-dev bc python3 pahole cpio pkg-config
```

Install perf using [this guide](https://stackoverflow.com/a/60276918/3049315).

Install the [custom WSL2 kernel](https://learn.microsoft.com/en-us/community/content/wsl-user-msft-kernel-v6) if necessary.

---

## Debug vs. Release Builds

- **Debug Builds**: Usually compiled with no optimizations and include extra debug symbols. They are slower and can provide different performance characteristics.
- **Release Builds**: Compiled with optimizations (e.g., `-O2` or `-O3`) to reflect production performance. Profiling release builds is recommended to understand real-world performance.

For profiling, always use **release builds with debug symbols** (`-g` along with optimization flags) to achieve accurate and useful performance data.

---

## Integrating Profiling and Benchmarking in CI/CD

### Current Landscape

- **Code Coverage**: Tools like Codecov or Coveralls are widely adopted for integrating code coverage data.
- **Profiling/Benchmarking**: There is no single, universal service for profiling results akin to code coverage services. However, you can:
  - **Store Artifacts**: CI/CD pipelines (GitHub Actions, GitLab CI/CD) can archive profiling output files (e.g., `gmon.out`, `callgrind.out.*`, `perf.data`) as artifacts for later analysis.
  - **JSON Output**: Some benchmarking tools (e.g., Google Benchmark) can output results in JSON format, which can be published to custom dashboards or parsed by CI scripts.
  - **Automated Reporting**: Integrate scripts that run benchmarks and then post summarized results to a Slack channel, a dashboard, or as comments on a merge request.
  - **Custom CI Jobs**: Create additional jobs in your CI pipeline that run profiling/benchmarking tools and then use artifact upload steps to preserve the results for offline analysis.

### Example in GitHub Actions

For instance, you could add a step to run Google Benchmark with JSON output and then use an action to upload the JSON file as an artifact:
```yaml
- name: Run C++ benchmarks with JSON output
  working-directory: cpp/build
  run: |
    ./vector_benchmark --benchmark_format=json > benchmark_results.json
- name: Upload Benchmark Results
  uses: actions/upload-artifact@v3
  with:
    name: benchmark-results
    path: cpp/build/benchmark_results.json
```
This way, while there isn’t a standardized “profiling dashboard” like Codecov, you can still capture and share performance data within your CI/CD workflow.

---

## Conclusion

This guide has detailed the following:
- **gprof**: Requires compiling with `-pg`; good for flat profiles and call graphs.
- **Valgrind (Callgrind)**: Provides detailed call graphs and instruction-level metrics; best analyzed with KCachegrind.
- **perf**: A versatile Linux tool for sampling-based profiling with live monitoring capabilities.

While integration of profiling results into CI/CD isn’t as standardized as for code coverage, you can still archive artifacts, use JSON outputs, and create custom reporting scripts to share performance data across your team.

Use this guide as a reference for setting up and using these profiling tools in your project, and adjust your CI/CD pipelines to capture and analyze performance data as needed.
