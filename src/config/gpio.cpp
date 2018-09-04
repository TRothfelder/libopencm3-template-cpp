/*
 * gpio.c
 *
 *  Created on: 27.05.2018
 *      Author: kt
 */
extern "C" {
	#include <libopencm3/stm32/rcc.h>
	#include <libopencm3/stm32/gpio.h>
	#include <libopencm3/stm32/spi.h>
}

#include "config/gpio.hpp"

void Gpio::setup( void ) {
	// For LED on D12
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);
	//for spi
	rcc_periph_clock_enable(RCC_GPIOA);
	//for led pin of disp
	rcc_periph_clock_enable(RCC_GPIOB);

	/*SPI Setup*/
	rcc_periph_clock_enable(RCC_SPI1);
	/* Configure GPIOs: DISP_CS=PD6, SCK=PA5, MISO=PA6 and MOSI=PA7 DISP_LED=PB10, DISP_RESET=PD5, DISP_DNC=PD4 */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE , GPIO5 | GPIO6 | GPIO7);
	gpio_set_af(GPIOA, GPIO_AF5, GPIO5 | GPIO6 | GPIO7 );


	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO5 | GPIO6 );
	//gpio_set(GPIOD, GPIO5);
	//gpio_set(GPIOD, GPIO6);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, GPIO4 );
	//gpio_clear(GPIOD, GPIO4);

	gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, GPIO10 );
	//gpio_set(GPIOB, GPIO10);

	/* Reset SPI, SPI_CR1 register cleared, SPI is disabled */
	spi_reset(SPI1);
	spi_disable_crc(SPI1);
	spi_set_dff_8bit(SPI1);
	spi_enable_software_slave_management(SPI1);
	spi_set_nss_high(SPI1);
	spi_set_baudrate_prescaler(SPI1, SPI_CR1_BR_FPCLK_DIV_8);
	spi_set_master_mode(SPI1);
	spi_set_clock_polarity_0(SPI1);
	spi_set_clock_phase_0(SPI1);
	spi_send_msb_first(SPI1);
	spi_enable(SPI1);


	/* Set GPIO12-15 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
}
