/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include "sdkconfig.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_DOT_PORT 853 /* Default TLS port */
#define DEFAULT_DOH_PORT 443 /* Default HTTPS port */

#define DEFAULT_DOT_TIMEOUT_MS 5000


typedef enum {
    DNS_PROTOCOL_UDP,           // Traditional UDP DNS (Port 53)
    DNS_PROTOCOL_TCP,           // TCP DNS (Port 53)
    DNS_PROTOCOL_DOT,           // DNS over TLS (Port 853)
    DNS_PROTOCOL_DOH,           // DNS over HTTPS (Port 443)
} esp_dns_protocol_type_t;

/* Define the configuration structure */
typedef struct {
    // Basic protocol selection
    esp_dns_protocol_type_t protocol;

    // Common settings
    const char *dns_server;  // DNS server IP or hostname
    //uint16_t port;               // Custom port (if default port is not used)
    uint32_t timeout_ms;         // Query timeout in milliseconds

    // Secure protocol options
    struct {
        const char *cert_pem;          // SSL server certification in PEM format as string
        esp_err_t (*crt_bundle_attach)(void *conf); // Function pointer to attach cert bundle
    } tls_config;                      // Used for DoT, DoH, DoH3, DNSCrypt, DoQ

    // Protocol-specific options
    union {
        // UDP DNS options
        struct {
            bool enable_edns0;        // Enable EDNS0 extensions
            uint16_t udp_payload_size; // EDNS0 UDP payload size
        } udp_config;

        // TCP DNS options
        struct {
            uint16_t keepalive_sec;   // TCP keepalive in seconds
        } tcp_config;

        // DoT options
        struct {
            const char *alpn;         // ALPN protocol string
            int port;
            int timeout_ms;
        } dot_config;

        // DoH options
        struct {
            const char *url_path;     // URL path for DoH Service (e.g., "/dns-query")
            int port;
        } doh_config;

    } protocol_config;

    // Advanced options
    bool ipv6_enabled;            // Enable IPv6 lookups
    uint8_t max_attempts;         // Max number of query attempts
} esp_dns_config_t;


typedef struct dns_handle* esp_dns_handle_t;


esp_dns_handle_t esp_dns_init(const esp_dns_config_t *config);

int esp_dns_cleanup(esp_dns_handle_t handle);

#ifdef __cplusplus
}
#endif
