#
# Copyright (c) 2024-2025, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BOARD 	:= a3m_ek_nor

APPLOAD	?= RZ_NOFIP
$(eval $(call add_define,APPLOAD))

include plat/renesas/rza/common/rz_common.mk

XSPI0_DEVICE		?=	qspiflash_mx25l25645g
XSPI_DEVICE_TYPE	:=	QSPI
$(eval $(call add_define_val,XSPI_DEVICE_TYPE,\"${XSPI_DEVICE_TYPE}\"))

NAND			:=	0
RZ_FLASH_SIZE		?=	33554432 # 32MB
$(eval $(call add_define,RZ_FLASH_SIZE))

ifneq (${USE_SDRAM},0)
ifeq (${DDR_PLL4},1333)
DDR_SOURCES		+=	plat/renesas/rza/soc/a3m/drivers/ddr/param_mc_C-011_D3-02-1.c	\
				plat/renesas/rza/common/drivers/ddr/param_swizzle_T1.c
else
DDR_PLL4		:= 	1600
DDR_SOURCES		+=	plat/renesas/rza/soc/a3m/drivers/ddr/param_mc_C-011_D3-01-1.c	\
				plat/renesas/rza/common/drivers/ddr/param_swizzle_T1.c
endif
$(eval $(call add_define,DDR_PLL4))
endif

include plat/renesas/rza/soc/a3m/rz_xspi.mk
include plat/renesas/rza/soc/a3m/soc.mk
