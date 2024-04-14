# Kickback Kube

A 3D matrix of LEDs that can simulate physics, cool animations, and much more. Designed to captivate any crowd, this platform combines interactive entertainment to make it ideal for keeping the party going past midnight.

## How to run and build

1. Run the following:
```
git clone git@github.com:Grace-Note-LLC/matrix-sim.git 
cd matrix-sim
g++ sim.cpp -o sim
```

2. Use
```
./sim -v -p 0
```
Note that `-c` is only used when `-p` is set to `0`.

```
    Usage: sudo ./sim [-v] [-c count] [-p preset] [-h help]
    Options:
      -v                        switch to verbose mode   
      -c value                  specify a value for count
      -h                        display this help message
      -p preset                 switch to a specific preset
```

## Software

### Core Components
`sim.cpp`: This is the central executable file where the main logic and integration of the simulations are handled. It controls the interactions between different modules and manages the overall program flow, including initializing the simulation environment, processing user inputs, and updating LED states based on simulation results.

### Presets

The presets are the following:

0. **Particle Simulation** (`particle_sim.h`): Handles simple particle physics simulations, including interactions with borders.


1. **Explode Simulation** (`explode_sim.h`): Simulates expanding wavefronts and explosive effects that radiate across the cube. 

2. **Snake Simulation** (`snake_sim.h`): A playful yet intricate module where a 'snake' traverses the entire grid in a continuous path, illuminating each LED once.

3. **Flash Simulation** (`flash_sim.h`): Generates sudden bursts of light, simulating effects such as lightning or other rapid illuminations within the cube. Useful for debugging.

4. **Loading Simulation** (`loading_sim.h`): Displays loading or progress animations that fill the cube gradually.

### Other Modules

**SPI Communication** (`spi.h`): Manages Serial Peripheral Interface (SPI) communications, crucial for controlling the LEDs and handling data transmission between the hardware components and the simulation software.


## Firmware




## Hardware
The hardware is a `4 x 4 x 4` 3D matrix of **LEDs**, where each *LED* is controlled by a microcontroller, the **SDM 32 F103C8T6**. The *SDM 32* is connected to a **Raspberry Pi 4**, which sends the data to the *SDM 32*. The *Pi* runs the software, which sends the data to the *SDM 32* over the **Serial Peripheral Interface (SPI)** Protocol.