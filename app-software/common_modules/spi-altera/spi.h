#ifndef SPI_H
#define SPI_H

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include <stdint.h>


class Spi
{
public:
    explicit Spi(const char *spi_path, uint8_t spi_mode);
    int  transfer(int len, char *tx, char *rx);

private:
    int  open_spi(const char *spi_device,  uint8_t mode);
    void pabort(const char *s);
    int open_device();
    void close_device(int fd);
    const char *spi_device;
    uint8_t mode;

};

#endif // SPI_H
