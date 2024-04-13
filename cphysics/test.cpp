#include <iostream>
#include <bitset>

int main() {
    std::bitset<64> bits("1010");

    // Check if the second bit is set (indexing from left to right starting from 0)
    bool isSecondBitSet = bits.test(1);
    std::cout << "Is the second bit set? " << isSecondBitSet << std::endl;

    // Set the third bit
    bits.set(2);
    std::cout << "Bits after setting the third bit: " << bits << std::endl;

    // Clear the first bit
    bits.reset(0);
    std::cout << "Bits after clearing the first bit: " << bits << std::endl;

    return 0;
}
