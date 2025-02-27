#include <benchmark/benchmark.h>
#include <unordered_map>
#include <random>

/**
 * @brief Benchmarks insertion in std::unordered_map.
 *
 * This benchmark measures the time taken to insert a number of key-value pairs
 * into a std::unordered_map.
 *
 * @param state A Google Benchmark state object.
 */
static void BM_UnorderedMapInsert(benchmark::State& state) {
    // Prepare random keys
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(0, state.range(0) * 10);

    for (auto _ : state) {
        std::unordered_map<int, int> m;
        m.reserve(state.range(0));
        for (int i = 0; i < state.range(0); ++i) {
            int key = dis(gen);
            m.insert({key, i});
        }
        benchmark::DoNotOptimize(m);
    }
}

BENCHMARK(BM_UnorderedMapInsert)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK_MAIN();
