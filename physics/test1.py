import numpy as np
from Particle import Particle


time_steps = 20  # Total number of time steps
dt = 0.1  # Time step duration

particles = [Particle()]

"""
Updates all particles positions. Note that all 
particles have automatic boundaary checking.
"""
def updateParticles(dt):
    for particle in particles:
        particle.updatePosition(dt)

"""
Returns a (3, n) array of n particles array
"""
def getParticlePositions():
    output = np.zeros((3, len(particles)))
    for particle in particles:
        output[:] = particle.getPosition()

    return output


# Simulation loop
for _ in range(time_steps):
    
    updateParticles(dt)

    print(f"Time step {_}: Position = \n{getParticlePositions()}")
