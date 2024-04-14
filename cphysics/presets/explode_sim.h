#include <tuple>

#if !defined(explode_sim_h)
#define explode_sim_h

#include "../sim.h"

#endif // explode_sim_h

vector<tuple<int8_t, int8_t, int8_t>> getEdges(int start) {
    vector<tuple<int8_t, int8_t, int8_t>> edges;

    for (int8_t x = start; x < CUBE_SIZE - start; x++) {
        for (int8_t y = start; y < CUBE_SIZE - start; y++) {
            for (int8_t z = start; z < CUBE_SIZE - start; z++) {
                if (x == start || x == CUBE_SIZE - start - 1 ||
                    y == start || y == CUBE_SIZE - start - 1 ||
                    z == start || z == CUBE_SIZE - start - 1) {
                    // std::cout << x << y << z << endl;
                    edges.push_back(make_tuple(x, y, z));
                    // std::cout << std::get<0>(edges[0]) << endl;
                }
            }
        }
    }

    return edges;
}


/*
Main loop to simulate explosion from center outwards.
*/
void explode_sim(int fd, bool verbose) {
    int lower = 0;

    // main time loop
    for (int t = 1; t <= TIME_STEPS; t++) {
        
        // get led coords from particles
        vector<tuple<int8_t, int8_t, int8_t>> led_coords = getEdges(lower);

        if (verbose) {
            for (auto a : led_coords) {
                printf("(%d,%d,%d)\n", std::get<0>(a), std::get<1>(a), std::get<2>(a));
            }
        }

        lower = (lower + 1) % CUBE_SIZE;

        // convert led coords to state vector
        bitset<LED_COUNT> bit_state = led_to_bit_state(&led_coords);
        // print state
        if (verbose) { 
            cout << t << "\t:\t" << bit_state << endl;
        } else {
            spi_write(fd, bits_to_byte(bit_state));
        }
    }
}