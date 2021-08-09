/*
 * Copyright (c) 2019-2022, Xilinx, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PM_API_SYS_H
#define PM_API_SYS_H

#include <stdint.h>
#include "pm_defs.h"

/**********************************************************
 * PM API function declarations
 **********************************************************/

enum pm_ret_status pm_handle_eemi_call(uint32_t flag, uint32_t x0, uint32_t x1,
				       uint32_t x2, uint32_t x3, uint32_t x4,
				       uint32_t x5, uint64_t *result);
enum pm_ret_status pm_self_suspend(uint32_t nid,
				   unsigned int latency,
				   unsigned int state,
				   uintptr_t address, uint32_t flag);
enum pm_ret_status pm_abort_suspend(enum pm_abort_reason reason, uint32_t flag);
enum pm_ret_status pm_req_suspend(uint32_t target,
				  uint8_t ack,
				  unsigned int latency,
				  unsigned int state, uint32_t flag);
enum pm_ret_status pm_req_wakeup(uint32_t target, uint32_t set_address,
				 uintptr_t address, uint8_t ack, uint32_t flag);
enum pm_ret_status pm_set_wakeup_source(uint32_t target, uint32_t device_id,
					uint8_t enable, uint32_t flag);
void pm_get_callbackdata(uint32_t *data, size_t count, uint32_t flag);
enum pm_ret_status pm_pll_set_param(uint32_t clk_id, uint32_t param,
				    uint32_t value, uint32_t flag);
enum pm_ret_status pm_pll_get_param(uint32_t clk_id, uint32_t param,
				    uint32_t *value, uint32_t flag);
enum pm_ret_status pm_pll_set_mode(uint32_t clk_id, uint32_t mode,
				   uint32_t flag);
enum pm_ret_status pm_pll_get_mode(uint32_t clk_id, uint32_t *mode,
				   uint32_t flag);
enum pm_ret_status pm_force_powerdown(uint32_t target, uint8_t ack,
				      uint32_t flag);
enum pm_ret_status pm_system_shutdown(uint32_t type, uint32_t subtype,
				      uint32_t flag);
enum pm_ret_status pm_api_ioctl(uint32_t device_id, uint32_t ioctl_id,
				uint32_t arg1, uint32_t arg2, uint32_t *value,
				uint32_t flag);
enum pm_ret_status pm_query_data(uint32_t qid, uint32_t arg1, uint32_t arg2,
				 uint32_t arg3, uint32_t *data, uint32_t flag);
unsigned int pm_get_shutdown_scope(void);
enum pm_ret_status pm_feature_check(uint32_t api_id, unsigned int *version,
				    uint32_t flag);
enum pm_ret_status pm_load_pdi(uint32_t src, uint32_t address_low,
			       uint32_t address_high, uint32_t flag);
enum pm_ret_status pm_register_notifier(uint32_t device_id, uint32_t event,
					uint32_t wake, uint32_t enable,
					uint32_t flag);
#endif /* PM_API_SYS_H */
