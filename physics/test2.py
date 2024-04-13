from itertools import combinations, product
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D

# Define the simulation parameters
cube_size = 10
initial_position = np.array([5, 5, 5], dtype=float)
initial_velocity = np.random.rand(3) * 2 - 1  # Random velocity
dt = 0.5  # Time step duration

# Set up the figure and 3D axis
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim(0, cube_size)
ax.set_ylim(0, cube_size)
ax.set_zlim(0, cube_size)
ax.grid(False)  # Turn off the grid
ax.set_xticklabels([])  # Remove axis labels
ax.set_yticklabels([])
ax.set_zticklabels([])
ax.xaxis.line.set_color((1.0, 1.0, 1.0, 0.0))  # Make axes lines invisible
ax.yaxis.line.set_color((1.0, 1.0, 1.0, 0.0))
ax.zaxis.line.set_color((1.0, 1.0, 1.0, 0.0))

# Draw the edges of the cube
for s, e in combinations(np.array(list(product([0, cube_size], repeat=3))), 2):
    if sum(np.abs(s-e)) == cube_size:
        ax.plot3D(*zip(s, e), color="b")

# Initialize particle position
particle, = ax.plot([initial_position[0]], [initial_position[1]], [initial_position[2]], 'ro')

def update(frame):
    global initial_position, initial_velocity
    # Update position
    initial_position += initial_velocity * dt
    # Boundary collision detection and response
    for i in range(3):
        if initial_position[i] <= 0 or initial_position[i] >= cube_size:
            initial_velocity[i] *= -1  # Reverse the velocity component on collision
    # Update the particle's position in the plot
    particle.set_data(initial_position[0], initial_position[1])
    particle.set_3d_properties(initial_position[2])
    return particle,

# Create animation
ani = FuncAnimation(fig, update, frames=200, interval=50, blit=True)

# Show the plot
plt.show()
