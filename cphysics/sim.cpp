#include "presets.h"

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
    int mode = 0;

    // cli parser
    while ((opt = getopt(argc, argv, "vc:hp:")) != -1) {
        switch (opt) {
            case 'v':           // enable verbose mode for debugging
                verbose = true;
                break;
            
            case 'c':           // number of particles (default 1)
                particle_count = atoi(optarg);
                break;

            case 'p':           // used later for presets
                mode = atoi(optarg);
                break;

            case 'h':           // prints help statement
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

    // mode executor
    switch (mode) {
        case 0:
            particle_sim(particle_count, verbose);
            break;
        case 1:
            explode_sim(verbose);
            break;
        case 2:
            snake_sim(verbose);
            break;
        case 3:
            flash_sim(verbose);
            break;
        case 4:
            loading_sim(verbose);
            break;

        default:
            cout << "Only cases [0-4] are allowed" << endl;
    }
    return 0;
}