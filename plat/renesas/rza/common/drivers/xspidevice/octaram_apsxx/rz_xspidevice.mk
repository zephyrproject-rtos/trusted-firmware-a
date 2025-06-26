#
# Copyright (c) 2021-2025, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

_XSPI_DEVICE	:=	octaram_apsxx
PLAT_INCLUDES	+=	-Iplat/renesas/rza/common/drivers/xspidevice/$(_XSPI_DEVICE)
RZ_XSPI_HEADERS	:=	$(RZ_XSPI_HEADERS) $(_XSPI_DEVICE)_api.h
RZ_XSPI_SOURCES	:=	$(RZ_XSPI_SOURCES) \
			plat/renesas/rza/common/drivers/xspidevice/$(_XSPI_DEVICE)/$(_XSPI_DEVICE).c
