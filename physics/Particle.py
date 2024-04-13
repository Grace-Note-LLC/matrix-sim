import numpy as np
from state import CUBE_SIZE

"""
    Particle class that stores position in a numpy array:
    self.position = [x, y, z] 
    self.velocity = [dx, dy, dz]

"""
class Particle:
    position = np.array([
        [CUBE_SIZE / 2],
        [CUBE_SIZE / 2],
        [CUBE_SIZE / 2]
    ])

    velocity = np.random.randn(3, 1)

    """
    Function to set the position of the particle.
    """
    def setPosition(self, X=position[0], Y=position[1], Z=position[2]):
        self.position[0] = X
        self.position[1] = Y
        self.position[2] = Z

    def getPosition(self):
        return self.position

    """
    Function to reset position of the particle.
    """
    def moveToCenter(self):
        self.position = np.array([
        CUBE_SIZE / 2,
        CUBE_SIZE / 2,
        CUBE_SIZE / 2
    ]) 
    
    """
    Function to set the velocity of the particle.
    """
    def setVelocity(self, dx=velocity[0], dy=velocity[1], dz=velocity[2]):
        self.velocity = np.array([dx, dy, dz])

    """
    Updates position based on velocity and time
    Functionally, 
    `(x,y,z) = (dx,dy,dz) * time` 
    component wise
    """
    def updatePosition(self, dt):
        self.position += self.velocity * dt

        # Check for collisions with the walls of the cube
        for i in range(3):
            if self.position[i] <= 0 or self.position[i] >= CUBE_SIZE:
                self.velocity[i] *= -1  # Reverse the velocity component on collision        