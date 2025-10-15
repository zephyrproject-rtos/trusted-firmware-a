#
# Copyright (c) 2021-2025, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

_XSPI_DEVICE	:=	octaflash_mx66uw
PLAT_INCLUDES	+=	-Idrivers/renesas/rza/xspidevice/octaflash_mx66uw
RZ_XSPI_HEADERS	:=	${RZ_XSPI_HEADERS} ${_XSPI_DEVICE}_api.h
RZ_XSPI_SOURCES	:=	${RZ_XSPI_SOURCES} \
			drivers/renesas/rza/xspidevice/${_XSPI_DEVICE}/${_XSPI_DEVICE}.c
