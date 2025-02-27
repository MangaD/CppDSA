#include <benchmark/benchmark.h>
#include <map>
#include <random>

/**
 * @brief Benchmarks insertion in std::map.
 *
 * This benchmark measures the time taken to insert a number of key-value pairs
 * into a std::map.
 *
 * @param state A Google Benchmark state object.
 */
static void BM_MapInsert(benchmark::State& state) {
    // Prepare random keys
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(0, state.range(0) * 10);

    for (auto _ : state) {
        std::map<int, int> m;
        for (int i = 0; i < state.range(0); ++i) {
            int key = dis(gen);
            m.insert({key, i});
        }
        benchmark::DoNotOptimize(m);
    }
}

BENCHMARK(BM_MapInsert)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK_MAIN();
