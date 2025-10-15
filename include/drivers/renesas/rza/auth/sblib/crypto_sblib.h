/*
 * Copyright (c) 2021-2025, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CRYPTO_SBLIB_H
#define CRYPTO_SBLIB_H

void crypto_sblib_init(void);

int crypto_sblib_auth(const void *key_cert, unsigned int key_cert_len,
		      const void *content_cert, unsigned int content_cert_len);

#endif /* CRYPTO_SBLIB_H */
