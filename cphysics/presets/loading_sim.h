#include <tuple>

#if !defined(loading_sim_h)
#define loading_sim_h

#include "../sim.h"

#endif // loading_sim_h

/*
Main loop to simulate snake moving.
*/
void loading_sim(int fd, bool verbose) {
    
    bitset<LED_COUNT> bit_state;

    // main time loop
    for (int t = 1; t <= TIME_STEPS; t++) {
        if (bit_state[0]) {
            if (verbose) cout << t << "\t:\t" << bit_state << endl;
            bit_state.reset();
            continue;
        }

        for (int i = 0; i < LED_COUNT / CUBE_SIZE; i++) {
            bit_state.set(LED_COUNT - i - 1);
        }

        // print state
        if (verbose) { 
            cout << t << "\t:\t" << bit_state << endl;
        } else {
            spi_write(fd, bits_to_byte(bit_state));
        }

        bit_state >>= LED_COUNT / CUBE_SIZE;
    }
}