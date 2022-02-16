#ifndef SSQ_H
#define SSQ_H

#include "ssq/error.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef _WIN32
# include <ws2tcpip.h>
#else
# include <sys/time.h>
# include <netdb.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif

enum ssq_timeout
{
    SSQ_TIMEOUT_RECV = 0x1,
    SSQ_TIMEOUT_SEND = 0x2
};

struct ssq_querier
{
    struct addrinfo *addr_list;
    struct ssq_error err;
#ifdef _WIN32
    DWORD            timeout_recv;
    DWORD            timeout_send;
#else
    struct timeval   timeout_recv;
    struct timeval   timeout_send;
#endif
};

/**
 * Initializes a new Source server querier.
 * @returns a new Source server querier or NULL if there was a memory allocation failure
 */
struct ssq_querier *ssq_init(void);

/**
 * Sets the target Source game server of a Source server querier.
 * @param querier the Source server querier
 * @param hostname target server's hostname
 * @param port target server's port number
 */
void ssq_set_target(struct ssq_querier *querier, const char *hostname, uint16_t port);

/**
 * Sets the sending/receiving timeouts of a Source server querier.
 * @param querier the Source server querier
 * @param timeout the timeouts to set (bitwise)
 * @param value the value to set in milliseconds
 */
void ssq_set_timeout(
    struct ssq_querier *querier,
    enum ssq_timeout    timeout,
#ifdef _WIN32
    DWORD               value
#else
    time_t              value
#endif
);

/**
 * Gets the last error code of a Source server querier.
 * Stands for SSQ ERRor Code.
 * @param querier the Source server querier
 * @returns the last error code of the Source server querier
 */
enum ssq_error_code ssq_errc(const struct ssq_querier *querier);

/**
 * Checks if there are any errors set on a Source server querier.
 * @param querier the Source server querier
 * @returns true if there are no errors
 */
bool ssq_ok(const struct ssq_querier *querier);

/**
 * Gets the last error message of a Source server querier.
 * Stands for SSQ ERRor Message.
 * @param querier the Source server querier
 * @returns the last error message of the Source server querier
 */
const char *ssq_errm(const struct ssq_querier *querier);

/**
 * Clears the error of a Source server querier.
 * @param querier the Source server querier
 */
void ssq_errclr(struct ssq_querier *querier);

/**
 * Frees a Source server querier.
 * @param querier the Source server querier to free
 */
void ssq_free(struct ssq_querier *querier);

#ifdef __cplusplus
}
#endif

#endif /* SSQ_H */
