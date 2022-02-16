#ifndef SSQ_QUERY_H
#define SSQ_QUERY_H

#include "ssq/ssq.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Sends a query and concatenates the payloads of the response packets into a single buffer.
 * @param querier the Source server querier to use
 * @param payload the query's payload
 * @param payload_len the query's payload length
 * @param response_len where to store the response buffer's length
 * @returns a buffer which corresponds to the concatenation of each packet's payload in the response
 */
char *ssq_query(
    struct ssq_querier *querier,
    const char          payload[],
#ifdef _WIN32
    int                 payload_len,
#else
    size_t              payload_len,
#endif
    size_t             *response_len
);

#ifdef __cplusplus
}
#endif

#endif /* SSQ_QUERY_H */
