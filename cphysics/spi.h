#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <bitset>
#include <tuple>

#if !defined(spi_h)
#define spi_h

#include "sim.h"

/*
Initializes the SPI protocol on the Raspberry Pi. Only works on UNIX 
devices. Note that in our case,

    /dev/spidev0.0    =    SPI0 CS0

which lets us write to the file as fd. The following options are
configurable:
- int mode
- int bits
- int speed

*/
int spi_init() {
    int fd;
    // SPI configuration
    int mode = SPI_MODE_0;
    int bits = 8;
    int speed = 500000;  // 500 kHz

    const char *device = "/dev/spidev0.0";  // Change as necessary
    // unsigned char data[] = {0x01, 0x37, 0xFF};
    // int length = sizeof(data);

    // Open SPI device
    fd = open(device, O_RDWR);
    if (fd < 0) {
        std::cerr << "Failed to open SPI device" << std::endl;
        return 1;
    }

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


    // // Close SPI device
    // if (close(fd) == -1) {
    //     std::cerr << "Failed to close SPI device" << std::endl;
    //     return 1;
    // }

    return fd;
}


/*
Writes to the SPI device directly (fd) from the data as (data).
*/
int spi_write(int fd, unsigned char *data) {
    size_t length = LED_COUNT / BITS_PER_BYTE;
    // Write data to SPI device
    if (write(fd, data, length) != static_cast<ssize_t>(length)) {
        std::cerr << "Failed to write data to SPI device" << std::endl;
        close(fd);
        return 1;
    }
    return 0;
}

/*
Simple bit converter to bytes.
*/
unsigned char* bits_to_byte(bitset<LED_COUNT> bit_state) {
    unsigned char* bytes = new unsigned char[LED_COUNT / BITS_PER_BYTE]; 
    for (int i = 0; i < BITS_PER_BYTE; i++) {
        bytes[i] = (bit_state >> (BITS_PER_BYTE * i)).to_ullong() & 0xFF;
    }
    return bytes;
}

#endif // spi_h