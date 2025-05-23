// xor_vs_regular_swap.cpp
// -------------------------------------------------------------
// Benchmark temp-var swap vs. XOR swap and log results to CSV.
// Build:  g++ -std=c++17 -O3 -march=native xor_vs_regular_swap.cpp -o swap_bench
// Run:    ./swap_bench [N]   (N = number of swaps, default 100'000'000)

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdint>
#include <cstdlib>

// -------------------------------------------------------------
// Two swap helpers
inline void swap_temp(uint32_t& a, uint32_t& b) noexcept
{
    uint32_t t = a;
    a = b;
    b = t;
}

inline void swap_xor(uint32_t& a, uint32_t& b) noexcept
{
    a ^= b;
    b ^= a;
    a ^= b;
}

// -------------------------------------------------------------
// Micro-benchmark driver
template <typename SwapFn>
double time_swaps(SwapFn&& swap_fn, std::size_t N)
{
    volatile uint32_t x = 0x12345678;
    volatile uint32_t y = 0xABCDEF01;

    const auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < N; ++i)
        swap_fn(const_cast<uint32_t&>(x), const_cast<uint32_t&>(y));
    const auto stop  = std::chrono::high_resolution_clock::now();

    static volatile uint32_t sink;
    sink = x ^ y;                     // keep compiler honest

    return std::chrono::duration<double>(stop - start).count();
}

// -------------------------------------------------------------
void log_csv(std::size_t N, double t_temp, double t_xor)
{
    const char* fname = "swap_results.csv";
    std::ifstream probe(fname);
    bool need_header = !probe.good();      // file absent → write header
    probe.close();

    std::ofstream out(fname, std::ios::app);
    if (need_header)
        out << "swaps,temp_seconds,xor_seconds,ratio\n";

    out << N << ',' << t_temp << ',' << t_xor << ',' << t_xor / t_temp << '\n';
}

// -------------------------------------------------------------
int main(int argc, char* argv[])
{
    const std::size_t N = (argc >= 2) ? std::strtoull(argv[1], nullptr, 10)
                                      : 100'000'000ULL;

    const double t_temp = time_swaps(swap_temp, N);
    const double t_xor  = time_swaps(swap_xor , N);

    std::cout << "Swaps performed       : " << N << '\n'
              << "Temp-var swap time    : " << t_temp << " s\n"
              << "XOR     swap time     : " << t_xor  << " s\n"
              << "XOR / Temp-var ratio  : " << t_xor / t_temp << "\n\n";

    log_csv(N, t_temp, t_xor);
    std::cout << "(Results appended to swap_results.csv)\n";
    return 0;
}
