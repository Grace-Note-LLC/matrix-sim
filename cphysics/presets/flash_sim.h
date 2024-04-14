#include <tuple>

#if !defined(flash_sim_h)
#define flash_sim_h

#include "../sim.h"

#endif // flash_sim_h

/*
Main loop to simulate snake moving.
*/
void flash_sim(int fd, bool verbose) {
    
    bitset<LED_COUNT> bit_state;
    bool toggle = true;

    // main time loop
    for (int t = 1; t <= TIME_STEPS; t++) {
        if (verbose) { 
            cout << t << "\t:\t" << bit_state << endl;
        } else {
            spi_write(fd, bits_to_byte(bit_state));
        }

        if (toggle) {
            bit_state.set();
            toggle = !toggle;
        } else {
            bit_state.reset();
            toggle = !toggle;
        }
    }
}