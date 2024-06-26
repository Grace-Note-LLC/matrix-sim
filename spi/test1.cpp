#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

int main() {
    int fd;
    const char *device = "/dev/spidev0.0";  // Change as necessary
    unsigned char data[] = {0x01, 0x37, 0xFF};
    int length = sizeof(data);

    // Open SPI device
    fd = open(device, O_RDWR);
    if (fd < 0) {
        std::cerr << "Failed to open SPI device" << std::endl;
        return 1;
    }

    // SPI configuration
    int mode = SPI_MODE_0;
    int bits = 8;
    int speed = 500000;  // 500 kHz

    // Set SPI mode
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {
        std::cerr << "Failed to set SPI mode" << std::endl;
        close(fd);
        return 1;
    }

    // Set bits per word
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1) {
        std::cerr << "Failed to set bits per word" << std::endl;
        close(fd);
        return 1;
    }

    // Set SPI clock speed
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
        std::cerr << "Failed to set SPI speed" << std::endl;
        close(fd);
        return 1;
    }

    // Write data to SPI device
    if (write(fd, data, length) != length) {
        std::cerr << "Failed to write data to SPI device" << std::endl;
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
