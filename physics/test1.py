import numpy as np

# Parameters
cube_size = 10  # Edge length of the cube
initial_position = np.array([5., 5., 5.])  # Starting point in the center
initial_velocity = np.array([1, 1, -1])  # Example velocity vector
time_steps = 100  # Total number of time steps
dt = 0.1  # Time step duration

# Initialize position and velocity
position = initial_position.copy()
velocity = initial_velocity.copy()

# Simulation loop
for _ in range(time_steps):
    # Update position
    position += velocity * dt

    # Check for collisions with the walls of the cube
    for i in range(3):
        if position[i] <= 0 or position[i] >= cube_size:
            velocity[i] *= -1  # Reverse the velocity component on collision

    # Print the position (you might want to visualize it instead)
    print(f"Time step {_}: Position = {position}")
