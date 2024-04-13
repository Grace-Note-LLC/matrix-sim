#include <cstdlib>  
#include <ctime>   
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Constants
const float dt = 0.2;
const int TIME_STEPS = 100;
const int CUBE_SIZE = 4;
const int LED_COUNT = CUBE_SIZE * CUBE_SIZE * CUBE_SIZE;
const int DEFAULT_NUM_PARTICLES = 1;
const int BITS_PER_BYTE = 8;
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
Converts particle positions into led coordinates depending on the size
*/
std::vector<std::tuple<int8_t, int8_t, int8_t>> particle_to_led(std::vector<Particle>* particles) {
    std:vector<std::tuple<int8_t, int8_t, int8_t>> led_coords;

    for (auto& p : *particles) {
        auto pos = p.get_position();

        // convert part

        led_coords.push_back(pos);
    }

    return led_coords;
}

std::bitset<LED_COUNT> led_to_state_vector(std::vector<std::tuple<int8_t, int8_t, int8_t>>* led_coords) {

    // speed up
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