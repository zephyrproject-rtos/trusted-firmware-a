#
# Copyright (c) 2021-2025, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

RZ_XSPI_DRIVER_PATH		:=	drivers/renesas/rza/xspi

RZ_XSPI_CONFIGS			:=	XSPI0 XSPI1 XSPI2
RZ_XSPI_SOURCES			:=	drivers/renesas/rza/xspi/xspi.c
RZ_XSPI_HEADERS			:=
RZ_XSPI0_IF			:=	spim
RZ_XSPI0_IF_CONFIG		:=	.channel=0, .base=0x10060000
RZ_XSPI1_IF			:=	octa
RZ_XSPI1_IF_CONFIG		:=	.channel=0, .base=0x10080000
RZ_XSPI2_IF			:=	octa
RZ_XSPI2_IF_CONFIG		:=	.channel=1, .base=0x10080000
RZ_XSPI_EXCLUSIVE_SELECTOR	:=	1
RZ_SPIM_SDR_FREQ_LIMIT		:=	66625000
RZ_OCTA_FREQ_LIMIT		:=	100000000

ifneq ($(strip $(XSPI0_DEVICE)),)
  ifneq ($(strip $(XSPI1_DEVICE)),)
    $(error XSPI0_DEVICE and XSPI1_DEVICE can not be specified at the same time.)
  endif
  ifneq ($(strip $(XSPI2_DEVICE)),)
    $(error XSPI0_DEVICE and XSPI2_DEVICE can not be specified at the same time.)
  endif
endif

PLAT_INCLUDES			+=	-Iinclude/drivers/renesas/rza/spim	\
					-Iinclude/drivers/renesas/rza/octal	\
					-Iinclude/drivers/renesas/rza/xspi

include plat/renesas/rza/common/rz_xspi_common.mk

$(eval $(call add_define,RZ_XSPI_EXCLUSIVE_SELECTOR))
$(eval $(call add_define,RZ_SPIM_SDR_FREQ_LIMIT))
$(eval $(call add_define,RZ_OCTA_FREQ_LIMIT))
