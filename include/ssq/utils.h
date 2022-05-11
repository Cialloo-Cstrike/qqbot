#ifndef SSQ_UTILS_H
#define SSQ_UTILS_H

#include "ssq/packet.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define S2A_CHALL 0x41

/**
 * Checks if the response has a challenge.
 * @returns true if the response's header is S2A_CHALL
 */
static inline bool ssq_utils_response_haschall(const char response[])
{
    const uint8_t header = response[0];
    return (header == S2A_CHALL);
}

/**
 * Checks if the response payload was truncated.
 * @returns true if the payload starts with 0xFFFFFFFF (single packet header)
 */
static inline bool ssq_utils_response_istruncated(const char response[])
{
    const int32_t header = *((int32_t *) response);
    return (header == A2S_PACKET_HEADER_SINGLE);
}

/**
 * Portable strncpy.
 */
static inline void ssq_utils_strncpy(char dst[], const char src[], const size_t n)
{
#if _WIN32
    strncpy_s(dst, n + 1, src, n);
#else
    strncpy(dst, src, n);
#endif
}

/**
 * Converts a port number to a string.
 * @param port the port number
 * @param buf the buffer to write to
 */
static inline void ssq_utils_porttostr(const uint16_t port, char buf[6])
{
#ifdef _WIN32
    sprintf_s(buf, 6, "%" PRIu16, port);
#else
    snprintf(buf, 6, "%" PRIu16, port);
#endif
}

#ifndef _WIN32

#include <sys/time.h>

/**
 * Converts a timeout in milliseconds to a timeval.
 * @param timeout the timeout value in milliseconds
 * @param tv the output timeval
 */
static inline void ssq_utils_mstotv(const time_t timeout, struct timeval *const tv)
{
    tv->tv_sec  = timeout / 1000;
    tv->tv_usec = timeout % 1000 * 1000;
}

#endif

#endif /* SSQ_UTILS_H */
