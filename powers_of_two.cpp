#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

// Function to check if a number is a power of two
bool isPowerOfTwo(unsigned int x) {
    // A number is a power of two if it has exactly one bit set in its binary representation.
    // This can be checked using the expression (x & (x - 1)) == 0.
    // Additionally, we need to ensure that x is not zero, as 0 is not a power of two.
    return x != 0 && (x & (x - 1)) == 0;
}

int main(){
    // Test cases to validate the isPowerOfTwo function
    assert(isPowerOfTwo(1));   // 2^0
    assert(isPowerOfTwo(2));   // 2^1
    assert(isPowerOfTwo(4));   // 2^2
    assert(isPowerOfTwo(8));   // 2^3
    assert(isPowerOfTwo(16));  // 2^4
    assert(isPowerOfTwo(32));  // 2^5
    assert(isPowerOfTwo(64));  // 2^6
    assert(isPowerOfTwo(128)); // 2^7
    assert(isPowerOfTwo(256)); // 2^8

    // Additional test cases
    assert(!isPowerOfTwo(0));   // 0 is not a power of two
    assert(!isPowerOfTwo(3));   // 3 is not a power of two  
    assert(!isPowerOfTwo(5));   // 5 is not a power of two
    assert(!isPowerOfTwo(6));   // 6 is not a power of two
    assert(!isPowerOfTwo(7));   // 7 is not a power of two
    assert(!isPowerOfTwo(9));   // 9 is not a power of two
    assert(!isPowerOfTwo(10));  // 10 is not a power of two

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}