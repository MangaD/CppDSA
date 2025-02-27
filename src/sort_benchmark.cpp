#include <benchmark/benchmark.h>
#include <algorithm>
#include <vector>
#include <random>

/**
 * @brief Benchmarks the performance of std::sort on a vector of random integers.
 *
 * The benchmark generates a vector of random integers of size state.range(0),
 * and then, in each iteration, it copies the vector and sorts the copy using std::sort.
 *
 * @param state A Google Benchmark state object.
 */
static void BM_VectorSort(benchmark::State& state) {
    // Generate a vector with random numbers
    std::vector<int> data(state.range(0));
    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::uniform_int_distribution<> dis(0, 100000);
    for (auto &elem : data) {
        elem = dis(gen);
    }

    // Benchmark loop
    for (auto _ : state) {
        // Copy the original unsorted data to ensure each iteration sorts the same set
        std::vector<int> copy = data;
        std::sort(copy.begin(), copy.end());
        benchmark::DoNotOptimize(copy);
    }
}

// Register the benchmark with varying vector sizes
BENCHMARK(BM_VectorSort)->Arg(1000)->Arg(10000)->Arg(100000);

// Main entry point for the benchmark executable
BENCHMARK_MAIN();
