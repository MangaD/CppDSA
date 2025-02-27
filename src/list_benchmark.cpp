#include <benchmark/benchmark.h>
#include <list>

/**
 * @brief Benchmarks the push_back operation on std::list.
 *
 * This benchmark measures the time taken to insert a number of integers into a std::list
 * using the push_back method.
 *
 * @param state A Google Benchmark state object.
 */
static void BM_ListPushBack(benchmark::State& state) {
    for (auto _ : state) {
        std::list<int> lst;
        // Insert state.range(0) elements
        for (int i = 0; i < state.range(0); ++i) {
            lst.push_back(i);
        }
        benchmark::DoNotOptimize(lst);
    }
}

// Register the benchmark with varying sizes
BENCHMARK(BM_ListPushBack)->Arg(1000)->Arg(10000)->Arg(100000);

// Main entry point for the benchmark executable
BENCHMARK_MAIN();
