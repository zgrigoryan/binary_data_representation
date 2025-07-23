// parse_png.cpp
//
// Build: g++ -std=c++20 -O2 -o parse_png parse_png.cpp
// Run:   ./parse_png swap_benchmark.png
//
// Prints header & IHDR fields; exits if the file isn't a valid PNG.

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#pragma pack(push,1)          // ── PNG structures are byte‑packed
struct ChunkHeader {
    uint32_t length_be;       // big‑endian
    char     type[4];
};
#pragma pack(pop)

static uint32_t be32(const uint8_t* p)
{
    return (uint32_t(p[0]) << 24) |
           (uint32_t(p[1]) << 16) |
           (uint32_t(p[2]) <<  8) |
            uint32_t(p[3]);
}

int main(int argc, char* argv[])
{
    if (argc != 2) { std::cerr << "usage: parse_png <file.png>\n"; return 1; }
    std::ifstream in(argv[1], std::ios::binary);
    if (!in) { std::perror("open"); return 1; }

    // ---- 1. check the 8‑byte PNG signature
    std::array<uint8_t,8> sig{};
    in.read(reinterpret_cast<char*>(sig.data()), 8);
    const uint8_t png_sig[8] = { 0x89,'P','N','G',0x0D,0x0A,0x1A,0x0A };
    if (!std::equal(sig.begin(), sig.end(), png_sig)) {
        std::cerr << "Not a PNG\n"; return 1;
    }
    std::cout << "PNG signature OK\n";

    // ---- 2. read the first chunk header (must be IHDR)
    ChunkHeader ch{};
    in.read(reinterpret_cast<char*>(&ch), sizeof(ch));
    uint32_t len = __builtin_bswap32(ch.length_be);      // convert BE→LE

    if (std::string(ch.type,4) != "IHDR" || len != 13) {
        std::cerr << "First chunk is not IHDR!\n"; return 1;
    }
    std::vector<uint8_t> ihdr(len);
    in.read(reinterpret_cast<char*>(ihdr.data()), len);

    uint32_t width      = be32(&ihdr[0]);
    uint32_t height     = be32(&ihdr[4]);
    uint8_t  bitDepth   = ihdr[8];
    uint8_t  colourType = ihdr[9];

    std::cout << "Width       : " << width  << '\n';
    std::cout << "Height      : " << height << '\n';
    std::cout << "Bit‑depth   : " << unsigned(bitDepth)   << '\n';
    std::cout << "Colour type : " << unsigned(colourType) << '\n';

    return 0;
}
