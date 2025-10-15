/*
 * Copyright (c) 2020-2025, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include <plat/common/common_def.h>
#include <plat_tzc_def.h>
#include <platform_def.h>

#include <arch.h>
#include <arch_helpers.h>
#include <common/bl_common.h>
#include <common/desc_image_load.h>
#include <drivers/generic_delay_timer.h>
#include <drivers/renesas/rza/console/scifa.h>
#include <drivers/renesas/rza/cpg/cpg.h>
#include <drivers/renesas/rza/ddr/ddr.h>
#include <drivers/renesas/rza/pfc/pfc.h>
#include <drivers/renesas/rza/syc/syc.h>
#include <drivers/renesas/rza/sys/sys_regs.h>
#include <drivers/renesas/rza/xspi/xspi_api.h>
#include <lib/mmio.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <rz_private.h>
#include <rza_ipl_version.h>
#include <rza_printf.h>

static console_t console;

/* Table of regions to map using the MMU. */
const mmap_region_t plat_mmap[] = {
	MAP_REGION_FLAT(0x00000000, 0x00200000, MT_MEMORY | MT_RW | MT_SECURE),
	MAP_REGION_FLAT(0x10000000, 0x10000000, MT_DEVICE | MT_RW | MT_SECURE),
	MAP_REGION_FLAT(0x20000000, 0x10000000, MT_MEMORY | MT_RW | MT_SECURE),
	MAP_REGION_FLAT(0x40000000, 0x40000000, MT_MEMORY | MT_RW | MT_SECURE),
	{ 0 }
};

int bl2_plat_handle_pre_image_load(unsigned int image_id)
{
	return 0;
}

int bl2_plat_handle_post_image_load(unsigned int image_id)
{
	static bl2_to_bl31_params_mem_t *params;
	bl_mem_params_node_t *bl_mem_params;

	if (!params) {
		params = (bl2_to_bl31_params_mem_t *)PARAMS_BASE;
		memset((void *)PARAMS_BASE, 0, sizeof(*params));
	}

	bl_mem_params = get_bl_mem_params_node(image_id);

	switch (image_id) {
	case BL32_IMAGE_ID:
		memcpy(&params->bl32_ep_info, &bl_mem_params->ep_info,
		       sizeof(entry_point_info_t));
		break;
	case BL33_IMAGE_ID:
		memcpy(&params->bl33_ep_info, &bl_mem_params->ep_info,
		       sizeof(entry_point_info_t));
		break;
	default:
		/* Do nothing in default case */
		break;
	}

	return 0;
}

void bl2_el3_early_platform_setup(u_register_t arg1, u_register_t arg2,
				  u_register_t arg3, u_register_t arg4)
{
	int ret;

	/* early setup Clock and Reset */
	cpg_early_setup();

	/* initialize SYC */
	syc_init(PLAT_SYC_INCK_HZ);

	/* initialize Timer */
	generic_delay_timer_init();

	/* setup PFC */
	pfc_setup();

	/* setup Clock and Reset */
	cpg_setup();

	/* initialize console driver */
	ret = console_scifa_register(PLAT_SCIF0_BASE, PLAT_UART_INCK_HZ,
				     PLAT_UART_BARDRATE, &console);
	if (!ret)
		panic();

	console_set_scope(&console, CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH);

	RZA_PRINTF("Initial Program Loader %s\n", RZA_IPL_VERSION_STRING);
}

void bl2_el3_plat_arch_setup(void)
{
	const mmap_region_t bl_regions[] = {
		MAP_REGION_FLAT(BL2_BASE, BL2_END - BL2_BASE,
				MT_MEMORY | MT_RW | MT_SECURE),
		MAP_REGION_FLAT(BL_CODE_BASE, BL_CODE_END - BL_CODE_BASE,
				MT_CODE | MT_SECURE),
		MAP_REGION_FLAT(BL_RO_DATA_BASE,
				BL_RO_DATA_END - BL_RO_DATA_BASE,
				MT_RO_DATA | MT_SECURE),
		{ 0 },
	};

	setup_page_tables(bl_regions, plat_mmap);

	enable_mmu_el3(0);
}

void bl2_platform_setup(void)
{
	/* Setup TZC-400, Access Control */
	plat_security_setup();

#if USE_SDRAM
	/* initialize DDR */
	ddr_setup();
#endif /* DEBUG_FPGA */

	xspi_setup();

	plat_rza_io_setup();

	RZ_RUN_TESTS();

#if (APPLOAD == RZ_NOFIP)
	rza_load_fsp();
#endif
	rza_print_descs();
}
