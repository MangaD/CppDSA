#include <benchmark/benchmark.h>
#include <vector>

/**
 * @brief Benchmarks the push_back operation on std::vector.
 *
 * This benchmark measures the time taken to insert a number of integers into a std::vector
 * using the push_back method.
 *
 * @param state A Google Benchmark state object, which provides the current benchmark iteration context.
 */
static void BM_VectorPushBack(benchmark::State& state) {
    // Each iteration of the benchmark:
    for (auto _ : state) {
        std::vector<int> vec;
        // Reserve space to avoid reallocations (optional)
        vec.reserve(state.range(0));
        // Insert state.range(0) elements
        for (int i = 0; i < state.range(0); ++i) {
            vec.push_back(i);
        }
        // Prevent the compiler from optimizing out the vector
        benchmark::DoNotOptimize(vec);
    }
}

// Register the benchmark function with varying sizes
BENCHMARK(BM_VectorPushBack)->Arg(1000)->Arg(10000)->Arg(100000);

// Main entry point for the benchmark executable
BENCHMARK_MAIN();
