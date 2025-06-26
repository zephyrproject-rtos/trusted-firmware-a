#
# Copyright (c) 2021-2025, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BOARD	:= a3ul_smarc_qspi

APPLOAD	?= RZ_NOFIP
$(eval $(call add_define,APPLOAD))

include plat/renesas/rza/common/rz_common.mk

XSPI0_DEVICE		?= qspiflash_at25
XSPI_DEVICE_TYPE	:= QSPI
$(eval $(call add_define_val,XSPI_DEVICE_TYPE,\"${XSPI_DEVICE_TYPE}\"))

NAND			:= 0
RZ_FLASH_SIZE 		?= 16777216 # 16MB
$(eval $(call add_define,RZ_FLASH_SIZE))

ifneq (${USE_SDRAM},0)
DDR_SOURCES		+=	plat/renesas/rza/soc/a3ul/drivers/ddr/param_mc_C-011_D4-01-2.c	\
				plat/renesas/rza/common/drivers/ddr/param_swizzle_T3bcud2.c

DDR_PLL4		:= 1600
$(eval $(call add_define,DDR_PLL4))
endif

include plat/renesas/rza/soc/a3ul/rz_xspi.mk
include plat/renesas/rza/soc/a3ul/soc.mk
