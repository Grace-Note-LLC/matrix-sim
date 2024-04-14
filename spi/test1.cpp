#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Open SPI device
    fd = open("/dev/spidev0.0", O_WRONLY);
    if (fd == -1) {
        std::cerr << "Failed to open SPI device" << std::endl;
        return 1;
    }

    // Write data to SPI device
    unsigned char data[] = {0x37, 0xFF};
    if (write(fd, data, sizeof(data)) == -1) {
        std::cerr << "Failed to write to SPI device" << std::endl;
        close(fd);
        return 1;
    }

    // Close SPI device
    if (close(fd) == -1) {
        std::cerr << "Failed to close SPI device" << std::endl;
        return 1;
    }

    return 0;
}
