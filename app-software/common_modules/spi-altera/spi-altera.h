#if !defined(SPI_ALTERA_H)
#define SPI_ALTERA_H

#include <stdint.h>
#include "spi.h"

class SpiAltera : public Spi
{
public:
    explicit SpiAltera(const char *spi_path);
    void reg_wr(uint16_t BaseReg, uint16_t AddrReg, uint32_t Dat);
    void reg_wr(uint16_t AddrReg, uint32_t Dat){
        reg_wr(0, AddrReg, Dat);
    };
    uint32_t reg_rd(uint16_t BaseReg, uint16_t AddrReg);
    uint32_t reg_rd(uint16_t AddrReg){
        return reg_rd(0, AddrReg);
    };
private:
    const unsigned int ALTERA_BUFF_SIZE = 6;
};

#endif // SPI_ALTERA_H
