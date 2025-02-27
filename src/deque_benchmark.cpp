#include <benchmark/benchmark.h>
#include <deque>

/**
 * @brief Benchmarks push_back operation on std::deque.
 *
 * This benchmark measures the time taken to insert a number of elements
 * into a std::deque using push_back.
 *
 * @param state A Google Benchmark state object.
 */
static void BM_DequePushBack(benchmark::State& state) {
    for (auto _ : state) {
        std::deque<int> dq;
        for (int i = 0; i < state.range(0); ++i) {
            dq.push_back(i);
        }
        benchmark::DoNotOptimize(dq);
    }
}

BENCHMARK(BM_DequePushBack)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK_MAIN();
