/*
 *  Atheros PB42 board support
 *
 *  Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>

#include <asm/mips_machine.h>
#include <asm/mach-ar71xx/ar71xx.h>
#include <asm/mach-ar71xx/pci.h>

#include "devices.h"

#define PB42_BUTTONS_POLL_INTERVAL	20

#define PB42_GPIO_BTN_SW4	8
#define PB42_GPIO_BTN_SW5	3

static struct spi_board_info pb42_spi_info[] = {
	{
		.bus_num	= 0,
		.chip_select	= 0,
		.max_speed_hz	= 25000000,
		.modalias	= "m25p80",
	}
};

static struct ar71xx_pci_irq pb42_pci_irqs[] __initdata = {
	{
		.slot	= 0,
		.pin	= 1,
		.irq	= AR71XX_PCI_IRQ_DEV0,
	}, {
		.slot	= 1,
		.pin	= 1,
		.irq	= AR71XX_PCI_IRQ_DEV1,
	}, {
		.slot	= 2,
		.pin	= 1,
		.irq	= AR71XX_PCI_IRQ_DEV2,
	}
};

static struct gpio_button pb42_gpio_buttons[] __initdata = {
	{
		.desc		= "sw4",
		.type		= EV_KEY,
		.code		= BTN_0,
		.threshold	= 5,
		.gpio		= PB42_GPIO_BTN_SW4,
		.active_low	= 1,
	} , {
		.desc		= "sw5",
		.type		= EV_KEY,
		.code		= BTN_1,
		.threshold	= 5,
		.gpio		= PB42_GPIO_BTN_SW5,
		.active_low	= 1,
	}
};

#define PB42_WAN_PHYMASK	BIT(20)
#define PB42_LAN_PHYMASK	(BIT(16) | BIT(17) | BIT(18) | BIT(19))
#define PB42_MDIO_PHYMASK	(PB42_LAN_PHYMASK | PB42_WAN_PHYMASK)

static void __init pb42_init(void)
{
	ar71xx_add_device_spi(NULL, pb42_spi_info,
				ARRAY_SIZE(pb42_spi_info));

	ar71xx_add_device_mdio(~PB42_MDIO_PHYMASK);

	ar71xx_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_MII;
	ar71xx_eth0_data.phy_mask = PB42_WAN_PHYMASK;

	ar71xx_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_RMII;
	ar71xx_eth1_data.phy_mask = PB42_LAN_PHYMASK;
	ar71xx_eth1_data.speed = SPEED_100;
	ar71xx_eth1_data.duplex = DUPLEX_FULL;

	ar71xx_add_device_eth(0);
	ar71xx_add_device_eth(1);

	ar71xx_add_device_gpio_buttons(-1, PB42_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(pb42_gpio_buttons),
				       pb42_gpio_buttons);

	ar71xx_pci_init(ARRAY_SIZE(pb42_pci_irqs), pb42_pci_irqs);
}

MIPS_MACHINE(AR71XX_MACH_PB42, "Atheros PB42", pb42_init);
