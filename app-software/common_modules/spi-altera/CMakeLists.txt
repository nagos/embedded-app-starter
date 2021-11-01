add_library(
	spi_altera
	spi-altera.cpp
	spi.cpp
)

add_executable(spi_reg_read
	spi_reg_read.cpp
)
target_link_libraries(spi_reg_read spi_altera)

add_executable(spi_reg_write
	spi_reg_write.cpp
)
target_link_libraries(spi_reg_write spi_altera)
INSTALL(TARGETS spi_reg_write spi_reg_read RUNTIME DESTINATION bin)
