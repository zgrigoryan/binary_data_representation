#include <iostream>
#include <cstdint>   // uint16_t

// ──────────────────────────────────────────────────────────────────────────
//  Detect whether <bit> and std::endian are available
#if __has_include(<bit>)            &&  (__cplusplus >= 202002L)
#   include <bit>
#   ifdef __cpp_lib_endian           // header is present *and* feature macro set
#       define HAS_STD_ENDIAN 1
#   else
#       define HAS_STD_ENDIAN 0
#   endif
#else
#   define HAS_STD_ENDIAN 0
#endif
// ──────────────────────────────────────────────────────────────────────────

// 1. Runtime probe (on any compiler)
bool isLittleEndianRuntime() {
    uint16_t n = 1;
    return *reinterpret_cast<char*>(&n) == 1;
}

// 2. Compile-time constant (constexpr)
constexpr bool isLittleEndianCompileTime() {
#if HAS_STD_ENDIAN
    return std::endian::native == std::endian::little;

#elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
    return __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__;

#elif defined(_WIN32)               // every supported Windows target is LE
    return true;

#else                               
    uint16_t n = 1;
    return *reinterpret_cast<const char*>(&n) == 1;
#endif
}

// ──────────────────────────────────────────────────────────────────────────
// Demo
int main() {
    std::cout << "Runtime : "
              << (isLittleEndianRuntime() ? "Little-endian" : "Big-endian") << '\n';

    std::cout << "Compile : "
              << (isLittleEndianCompileTime() ? "Little-endian" : "Big-endian") << '\n';

#if HAS_STD_ENDIAN || defined(__BYTE_ORDER__) || defined(_WIN32)
    static_assert(isLittleEndianCompileTime(),
                  "Compile-time endianness detection failed!");
#endif
}