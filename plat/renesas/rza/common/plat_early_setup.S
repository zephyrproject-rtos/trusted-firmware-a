/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <common/bl_common.h>

#define SYS_REG_BASE				(0x1102)
#define SYS_REG_LSI_MODE			(0xA00)
#define SYS_BITPOS_LSI_MODE_STAT_DEBUGEN	(9)

#define WAIT_CNT_HIGH16		(0x100)
#define WAIT_CNT_LOW16		(0)

	.globl	plat_setup_early_console


func plat_setup_early_console
	/* clear icache (SCTLR_EL3 init) */
	mov_imm	x4, (SCTLR_RESET_VAL & ~(SCTLR_EE_BIT | SCTLR_WXN_BIT | SCTLR_SA_BIT | \
					 SCTLR_A_BIT | SCTLR_DSSBS_BIT))
	msr	sctlr_el3, x4
	isb

	/* check DEBUGEN */
	mov	x4, #SYS_REG_LSI_MODE
	movk	x4, #SYS_REG_BASE, LSL #16
	ldr	w5, [x4]
	/* skip wait if DEBUGEN = 0 */
	tbz	x5, #SYS_BITPOS_LSI_MODE_STAT_DEBUGEN, skip_wait

	/* wait */
	mov	x4, #WAIT_CNT_LOW16
	movk	x4, #WAIT_CNT_HIGH16, LSL #16
wait_loop:
	cbz	x4, skip_wait
	sub	x4, x4, #1
	b	wait_loop
skip_wait:
	ret
endfunc plat_setup_early_console
