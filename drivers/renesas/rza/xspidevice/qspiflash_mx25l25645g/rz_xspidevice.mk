#
# Copyright (c) 2024-2025, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

_XSPI_DEVICE	:=	qspiflash_mx25l25645g
PLAT_INCLUDES	+=	-Idrivers/renesas/rza/xspidevice/qspiflash_mx25l25645g
RZ_XSPI_HEADERS	:=	${RZ_XSPI_HEADERS} ${_XSPI_DEVICE}_api.h
RZ_XSPI_SOURCES	:=	${RZ_XSPI_SOURCES} \
			drivers/renesas/rza/xspidevice/${_XSPI_DEVICE}/${_XSPI_DEVICE}.c
