/**
 * Чтение и запись регистров для verilog модуля prft-spi-avalon
 */

#include "spi-altera.h"

SpiAltera::SpiAltera(const char *spi_path)
    : Spi(spi_path, SPI_MODE_0)
{
}

void SpiAltera::reg_wr(uint16_t BaseReg, uint16_t AddrReg, uint32_t Dat)
{
    char tx_buff[ALTERA_BUFF_SIZE];
    unsigned int reg_addr_full = BaseReg/4 + AddrReg;

    tx_buff[0]  = reg_addr_full >> 8;
    tx_buff[1]  = reg_addr_full;
    tx_buff[0] |= 0x80;

    tx_buff[2] = Dat >> (8 * 3);
    tx_buff[3] = Dat >> (8 * 2);
    tx_buff[4] = Dat >> (8 * 1);
    tx_buff[5] = Dat;

    transfer(ALTERA_BUFF_SIZE, tx_buff, NULL);
}

uint32_t SpiAltera::reg_rd(uint16_t BaseReg, uint16_t AddrReg)
{
    char tx_buff[ALTERA_BUFF_SIZE];
    char rx_buff[ALTERA_BUFF_SIZE];
    uint32_t Dat;

    unsigned int reg_addr_full = BaseReg/4 + AddrReg;

    tx_buff[0] = reg_addr_full >> 8;
    tx_buff[1] = reg_addr_full;

    transfer(ALTERA_BUFF_SIZE, tx_buff, rx_buff);

    Dat  = rx_buff[2] << (8 * 3);
    Dat |= rx_buff[3] << (8 * 2);
    Dat |= rx_buff[4] << (8 * 1);
    Dat |= rx_buff[5];

    return Dat;
}
