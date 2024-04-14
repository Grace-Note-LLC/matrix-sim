#include <tuple>

#if !defined(particle_sim_h)
#define particle_sim_h

#include "../sim.h"
#include "../spi.h"


#endif // particle_sim_h

using namespace std;

const float dt = 0.2;
const int DEFAULT_NUM_PARTICLES = 1;

/*
Particle class to be updated, print position, etc.
*/
class Particle {
private:
    float position[3];
    float velocity[3];

public:
    /*
    Constructor to initialize the particle
    */
    Particle() {
        position[0] = CUBE_SIZE / 2;
        position[1] = CUBE_SIZE / 2;
        position[2] = CUBE_SIZE / 2;

        // Random initial velocity
        velocity[0] = static_cast<float>(std::rand()) / RAND_MAX * 2 - 1;
        velocity[1] = static_cast<float>(std::rand()) / RAND_MAX * 2 - 1;
        velocity[2] = static_cast<float>(std::rand()) / RAND_MAX * 2 - 1;
    }

    /*
    Update the particle's position and handle collisions
    */
    void update() {
        for (int i = 0; i < 3; i++) {
            position[i] += velocity[i] * dt;

            // Check for collisions with the walls of the cube
            if (position[i] <= 0 || position[i] >= CUBE_SIZE) {
                velocity[i] *= -1;  // Reverse the velocity component on collision
            }
        }
    }

    /*
    Output the current position of the particle
    */
    void print_position(int step) const {
        std::cout << "(" << position[0] << ", " << position[1] << ", " << position[2] << ")" << std::endl;
    }

    /*
    Sets particle velocity.
    */
    void set_velocity() {
        velocity[0] = static_cast<float>(std::rand()) / RAND_MAX * 2 - 1;
        velocity[1] = static_cast<float>(std::rand()) / RAND_MAX * 2 - 1;
        velocity[2] = static_cast<float>(std::rand()) / RAND_MAX * 2 - 1;
    }

    /*
    Gets tuple of positions.
    */
    std::tuple<float, float, float> get_position() {
        return std::make_tuple(position[0], position[1], position[2]);
    }
};

/*
Prints each particle's position.
*/
void particle_print(std::vector<Particle>* particles, int t) {
    for (const auto& p : *particles) {
        p.print_position(t);
    }
}

/*
Update all particles in particle array.
*/
void update_all(std::vector<Particle>* particles) {
    for (auto& p : *particles) {
        p.update();
    }
}

/*
Makes sure the rounded values are within the cube's bounds. Only input 
rounded values
*/
int bound_fix(int val) {
    if (val < 0) {
        return 0;
    }
    else if (val >= CUBE_SIZE) {
        return CUBE_SIZE - 1;
    }
    else {
        return val;
    }
}

/*
Converts particle positions into led coordinates depending on the size
*/
std::vector<std::tuple<int8_t, int8_t, int8_t>> particle_to_led(std::vector<Particle>* particles) {
    std:vector<std::tuple<int8_t, int8_t, int8_t>> led_coords;

    for (auto& p : *particles) {
        auto pos = p.get_position();

        // convert part
        tuple<int8_t, int8_t, int8_t> led_coord = make_tuple(
            bound_fix(round(get<0>(pos))),
            bound_fix(round(get<1>(pos))),
            bound_fix(round(get<2>(pos)))
        );

        led_coords.push_back(led_coord);
    }

    return led_coords;
}

/*
Main loop to simulate particles.
*/
void particle_sim(int fd, int particle_count, bool verbose) {
    vector<Particle> particles(particle_count);

    // main time loop
    for (int t = 1; t <= TIME_STEPS; t++) {
        // update all particles
        update_all(&particles);

        // if (verbose) particle_print(&particles, t);

        // get led coords from particles
        vector<tuple<int8_t, int8_t, int8_t>> led_coords = particle_to_led(&particles);

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