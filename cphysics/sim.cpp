#include "sim.h"
#include <getopt.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <bitset>

using namespace std;

int main(int argc, char *argv[]) {
    int opt;
    bool verbose = false;
    int particle_count = DEFAULT_NUM_PARTICLES;

    // cli parser
    while ((opt = getopt(argc, argv, "vc:hp")) != -1) {
        switch (opt) {

            // enable verbose mode for debugging
            case 'v':
                verbose = true;
                break;
            
            // number of particles (default 1)
            case 'c':
                particle_count = atoi(optarg);
                // cout << particle_count;
                break;

            // used later for presets
            case 'p':
                // does nothing for now
                break;

            // prints help statement
            case 'h':
                cout << "Usage: " << argv[0] << " [--count value] [-h]\n";
                cout << "Options:\n";
                cout << "  -v                        switch to verbose mode   \n";
                cout << "  -c value                  specify a value for count\n";
                cout << "  -h                        display this help message\n";
                cout << "  -p preset                 switch to a specific preset\n";
                exit(EXIT_SUCCESS);
            default:
                cerr << "Usage: " << argv[0] << " [-c value] [-v]\n";
        }
    }

    std::vector<Particle> particles(particle_count);

    // main time loop
    for (int t = 0; t < TIME_STEPS; t++) {

        // update all particles
        update_all(&particles);

        if (verbose) particle_print(&particles, t);

        // get led coords from particles
        std:vector<std::tuple<int8_t, int8_t, int8_t>> led_coords = particle_to_led(&particles);

        // convert led coords to state vector
        std::bitset<LED_COUNT> bit_state = led_to_state_vector(&led_coords);

    }

    return 0;
}