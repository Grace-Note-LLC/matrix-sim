#include <tuple>

#if !defined(snake_sim_h)
#define snake_sim_h

#include "../sim.h"

#endif // snake_sim_h

/*
Main loop to simulate snake moving.
*/
void snake_sim(int fd, bool verbose) {
    
    bitset<LED_COUNT> bit_state;
    bit_state.set(LED_COUNT - 1);
    bit_state.set(LED_COUNT - 2);
    bit_state.set(LED_COUNT - 3);

    // main time loop
    for (int t = 1; t <= TIME_STEPS; t++) {
        // print state
        if (verbose) { 
            cout << t << "\t:\t" << bit_state << endl;
        } else {
            spi_write(fd, bits_to_byte(bit_state));
        }

        bit_state >>= 1;
        if (bit_state.none()) {
            bit_state.set(LED_COUNT - 1);
            bit_state.set(LED_COUNT - 2);
            bit_state.set(LED_COUNT - 3);
        }
    }
}