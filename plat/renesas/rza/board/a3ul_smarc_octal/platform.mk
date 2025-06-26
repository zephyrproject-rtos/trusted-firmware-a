#
# Copyright (c) 2021-2025, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BOARD	:= a3ul_smarc_octal

APPLOAD	?= RZ_NOFIP
$(eval $(call add_define,APPLOAD))

include plat/renesas/rza/common/rz_common.mk

XSPI1_DEVICE		?=	octaflash_mx66uw
XSPI1_IF_OPTION		?=	.device_size=128*1024*1024
XSPI2_DEVICE		?=	octaram_apsxx
XSPI2_IF_OPTION		?=	.device_size=64*1024*1024
XSPI_DEVICE_TYPE	:=	OCTA
$(eval $(call add_define_val,XSPI_DEVICE_TYPE,\"${XSPI_DEVICE_TYPE}\"))

NAND			:=	0
RZ_FLASH_SIZE		?=	134217728 # 128MB
$(eval $(call add_define,RZ_FLASH_SIZE))

ifneq (${USE_SDRAM},0)
DDR_SOURCES		+=	plat/renesas/rza/soc/a3ul/drivers/ddr/param_mc_C-011_D4-01-2.c	\
				plat/renesas/rza/common/drivers/ddr/param_swizzle_T3bcud2.c

DDR_PLL4		:=	1600
$(eval $(call add_define,DDR_PLL4))
endif

include plat/renesas/rza/soc/a3ul/rz_xspi.mk
include plat/renesas/rza/soc/a3ul/soc.mk
