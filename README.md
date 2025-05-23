# 🧩 Binary-Data Playground  
Tiny C++ (and one Python) experiments that illustrate how **bits, bytes, and CPU
instructions** behave under the hood.

| Topic | File(s) | What it demonstrates |
|-------|---------|----------------------|
| Endianness detection | `detecting_endianness.cpp` | How to check byte order at **runtime** *and* at **compile time** (C++20 `std::endian`, compiler macros, or a constexpr fallback). |
| Powers of two | `powers_of_two.cpp` | A branch-free bit-hack to test if an integer is a power of two + unit tests with `assert`. |
| XOR vs. regular swap | `xor_vs_regular_swap.cpp` → `swap_bench` | Benchmarks the famous XOR-swap trick vs. the classic temp-var swap, logs CSV results, and even generates a PNG chart via Python. |

---

## 1  Why does this repo exist?
Modern high-level C++ can still poke the very lowest levels of a computer
architecture. Each snippet focuses on a **single micro-topic**:

* **Endianness** – why does `0x0001` sometimes live in memory as `01 00` and
  sometimes as `00 01`?  
* **Bit-hacks** – how can one line (`x & (x-1)`) reveal a power of two?  
* **Micro-benchmarks** – are “cool” tricks like XOR swap still faster on 2020s
  hardware? 

Together they form a lightweight **reference / playground** for students who
want to *see* what happens inside the CPU rather than just read about it.

---

## 2  Quick build & run

### 2.1  Prerequisites
* **C++17** (or newer) compiler – tested with Clang 17 and GCC 13  
  *`detecting_endianness.cpp` will optionally use `<bit>` if you compile in
  C++20.*
* **Python 3.8+** (only for the visualisation)  
  ```bash
  # Conda or pip – choose one:
  conda install pandas matplotlib           # recommended in a Conda env
  # pip install --user pandas matplotlib    # universal fallback
  ```

### 2.2  One-shot with plain `g++`

```bash
# Endianness probe
g++ -std=c++17 -O2 detecting_endianness.cpp -o endian
./endian

# Power-of-two test
g++ -std=c++17 -O2 powers_of_two.cpp -o pow2
./pow2          # prints: All test cases passed!

# XOR vs. regular swap benchmark
g++ -std=c++17 -O3 -march=native xor_vs_regular_swap.cpp -o swap_bench
./swap_bench            # default 100 M swaps
./swap_bench 20000000   # custom number of swaps

# Visualise the last run
python swaps.py         # or python plot_swaps_nopandas.py
open swap_benchmark.png # macOS example – open the generated chart
```

---

## 3  File overview

```
.
├─ .github/workflows/           # CI pipeline
├─ CMakeLists.txt               # top-level CMake
├─ detecting_endianness.cpp     # runtime + compile-time endianness demo
├─ powers_of_two.cpp            # branch-free power-of-two checker + tests
├─ xor_vs_regular_swap.cpp      # benchmark → ./swap_bench
├─ swap_results.csv             # CSV log (appended by every run)
├─ swap_benchmark.png           # matplotlib bar chart
├─ swaps.py                     # pandas + matplotlib visualiser
└─ plot_swaps_nopandas.py       # fallback: stdlib csv + matplotlib only
```

---

## 4  Sample output

```
$ ./endian
Runtime : Little-endian
Compile : Little-endian

$ ./swap_bench 50000000
Swaps performed       : 50000000
Temp-var swap time    : 0.09 s
XOR     swap time     : 0.31 s
XOR / Temp-var ratio  : 3.44

(Results appended to swap_results.csv)
```

…and `swap_benchmark.png`:
![swap_benchmark.png](swap_benchmark.png)

---
