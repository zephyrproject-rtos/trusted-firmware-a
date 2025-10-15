/*
 * Copyright (c) 2020-2025, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>

#include <lib/mmio.h>

#define SYC_BASE PLAT_SYC_BASE

static inline void syc_reg_write(uint32_t offset, uint32_t val)
{
	mmio_write_32(SYC_BASE + offset, val);
}

static inline uint32_t syc_reg_read(uint32_t offset)
{
	return mmio_read_32(SYC_BASE + offset);
}

static void enable_counter(unsigned int enable)
{
	syc_reg_write(CNTCR_OFF, enable & CNTCR_EN);
}

void syc_init(unsigned int freq)
{
	syc_reg_write(CNTFID_OFF, freq);
	enable_counter(CNTCR_EN);
}

unsigned int syc_get_freq(void)
{
	return syc_reg_read(CNTFID_OFF);
}
