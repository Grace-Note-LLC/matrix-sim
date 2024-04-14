#include <cstdlib>  
#include <ctime>   
#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

// Constants
const int TIME_STEPS = 100;
const int CUBE_SIZE = 4;
const int LED_COUNT = CUBE_SIZE * CUBE_SIZE * CUBE_SIZE;
const int BITS_PER_BYTE = 8;

/*
Converts LED coordinates into bit state
*/
std::bitset<LED_COUNT> led_to_bit_state(std::vector<std::tuple<int8_t, int8_t, int8_t>>* led_coords) {
    std::bitset<LED_COUNT> output;

    // god forsaken O(k) solution that beats O(n^3) 
    for (auto coord : *led_coords) {
        int state_idx = 
            CUBE_SIZE * CUBE_SIZE * std::get<2>(coord) +
            CUBE_SIZE * std::get<1>(coord) +
            std::get<0>(coord);
        
        // index of bit set starts from right, so subtract
        output.set(LED_COUNT - state_idx);
    }

    return output;
}
