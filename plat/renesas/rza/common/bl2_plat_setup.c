/*
 * Copyright (c) 2020-2025, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <string.h>

#include <plat/common/common_def.h>
#include <plat_tzc_def.h>
#include <platform_def.h>

#include <arch.h>
#include <arch_helpers.h>
#include <common/bl_common.h>
#include <common/desc_image_load.h>
#include <cpg.h>
#include <ddr.h>
#include <drivers/generic_delay_timer.h>
#include <lib/mmio.h>
#include <lib/xlat_tables/xlat_tables_compat.h>
#include <pfc.h>
#include <rz_private.h>
#include <rza_ipl_version.h>
#include <rza_mmu.h>
#include <rza_printf.h>
#include <scifa.h>
#include <syc.h>
#include <sys_regs.h>

static console_t console;

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
	ret = console_rza_register(PLAT_SCIF0_BASE, PLAT_UART_INCK_HZ,
				   PLAT_UART_BARDRATE, &console);
	if (!ret)
		panic();

	console_set_scope(&console, CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH);

	RZA_PRINTF("Initial Program Loader %s\n", RZA_IPL_VERSION_STRING);
}

void bl2_el3_plat_arch_setup(void)
{
	rza_mmu_pgtbl_cfg_t g_mmu_pagetable_array[] = {
		/* vaddress, paddress,   size,       attribute */
		{ 0x00000000, 0x00000000, 0x00200000,
		  RZA_MMU_ATTRIBUTE_NORMAL_CACHEABLE },
		{ 0x00200000, 0x00200000, 0x0FE00000,
		  RZA_MMU_ATTRIBUTE_ACCESS_FAULT },
		{ 0x10000000, 0x10000000, 0x10000000,
		  RZA_MMU_ATTRIBUTE_DEVICE },
		{ 0x20000000, 0x20000000, 0x10000000,
		  RZA_MMU_ATTRIBUTE_NORMAL_CACHEABLE },
		{ 0x30000000, 0x30000000, 0x10000000,
		  RZA_MMU_ATTRIBUTE_ACCESS_FAULT },
		{ 0x40000000, 0x40000000, 0x40000000,
		  RZA_MMU_ATTRIBUTE_NORMAL_CACHEABLE },
		{ 0x80000000, 0x80000000, 0x40000000,
		  RZA_MMU_ATTRIBUTE_ACCESS_FAULT },
		{ 0xC0000000, 0xC0000000, 0x40000000,
		  RZA_MMU_ATTRIBUTE_ACCESS_FAULT },
		{ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		  RZA_MMU_ATTRIBUTE_CONFIG_END }
	};

	if (0 != plat_mmu_init(g_mmu_pagetable_array)) {
		panic();
	}
	plat_mmu_enable();
}

void bl2_platform_setup(void)
{
	/* Setup TZC-400, Access Control */
	plat_security_setup();

#if USE_SDRAM
	/* initialize DDR */
	ddr_setup();
#endif /* DEBUG_FPGA */

	rz_io_setup();

	RZ_RUN_TESTS();

#if (APPLOAD == RZ_NOFIP)
	rza_load_fsp();
#endif
	rza_print_descs();
}
