#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

int main() {
    int fd;
    int addr = 0x40;  // Example I2C address

    // Open I2C device
    fd = open("/dev/i2c-20", O_RDWR);
    if (fd == -1) {
        std::cerr << "Failed to open I2C device" << std::endl;
        return 1;
    }

    // Set I2C slave address
    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        std::cerr << "Failed to acquire bus access and/or talk to slave." << std::endl;
        close(fd);
        return 1;
    }

    // Additional code for communication would go here

    // Close I2C device
    if (close(fd) == -1) {
        std::cerr << "Failed to close I2C device" << std::endl;
        return 1;
    }

    return 0;
}
