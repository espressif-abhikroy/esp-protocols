/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "esp_dns_tcp.h"

#define TAG "ESP_DNS_TCP"

/* ========================= TCP DNS FUNCTIONS ========================= */

int init_tcp_dns(esp_dns_handle_t handle)
{
    ESP_LOGI(TAG, "Initializing TCP DNS");

    set_error(handle, DNS_ERR_NOT_IMPLEMENTED, "TCP DNS not implemented yet");

    return 0;
}

int cleanup_tcp_dns(esp_dns_handle_t handle)
{
    ESP_LOGI(TAG, "Cleaning up TCP DNS");

    return 0;
}

err_t dns_resolve_tcp(const esp_dns_handle_t handle, const char *name, ip_addr_t *addr, u8_t rrtype)
{
    // TODO: Implement TCP DNS resolution
    if (addr == NULL) {
        return ERR_ARG;
    }

    /* Return hardcoded IP based on requested record type */
    if (rrtype == DNS_RRTYPE_A) {
        /* Return IPv4 address 192.168.1.100 */
        IP_ADDR4(addr, 192, 168, 1, 100);
    } else if (rrtype == DNS_RRTYPE_AAAA) {
        /* Return IPv6 address fe80::1 */
        IP_ADDR6(addr, 0xfe800000, 0, 0, 1);
    } else {
        return ERR_VAL; /* Unsupported record type */
    }

    return ERR_OK;
}
