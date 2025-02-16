#include <benchmark/benchmark.h>
#include <iostream>
#include <tuple>
#include "qpp/qpp.hpp"
using namespace qpp;

auto measure() {
    ket psi = 00_ket;
    cmat U = gt.CNOT * kron(gt.H, gt.Id2);
    ket result = U * psi; // we have the Bell state (|00> + |11>) / sqrt(2)
    result = apply(result, gt.X, {1}); // we produced (|01> + |10>) / sqrt(2)
    auto [m, probs, states] = measure(result, gt.H, {0});
    return states;
}

// Benchmark for matrix multiplication
static void BM_MatrixMultiplication(benchmark::State& state) {

    for (auto&& elem : state) {
        auto state1 = measure();
        auto state2 = measure();
        benchmark::DoNotOptimize(state1);
        benchmark::DoNotOptimize(state2);
    }
}
BENCHMARK(BM_MatrixMultiplication);

BENCHMARK_MAIN();
