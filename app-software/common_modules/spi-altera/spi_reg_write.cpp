#include <unistd.h>
#include <iostream>
#include "spi-altera.h"

unsigned int reg_base = 0;
unsigned int reg_addr = 0;
unsigned int reg_value = 0;
const char * spi_path = "";

static void usage()
{
    printf("USAGE: spi_reg_write SPIDEV BASE ADDR VALUE\n");
}

static int parse_opt(int argc, char *argv[])
{
    if (argc < 5) {
        usage();
        return 1;
    }

    spi_path = argv[1];
    reg_base = std::stoi(argv[2], 0, 0);
    reg_addr = std::stoi(argv[3], 0, 0);
    reg_value = std::stoi(argv[4], 0, 0);

    return 0;
}

int main(int argc, char* argv[])
{
    printf("PRFT-SPI-AVALON register write\n");
    if (parse_opt(argc, argv)) return 1;

    SpiAltera spi(spi_path);
    spi.reg_wr(reg_base, reg_addr, reg_value);

    printf("%04x.%04x = %02x\n", reg_base, reg_addr, reg_value);

    return 0;
}
