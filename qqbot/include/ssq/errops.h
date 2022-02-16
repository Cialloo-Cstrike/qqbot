#ifndef SSQ_ERROPS_H
#define SSQ_ERROPS_H

#include "ssq/error.h"

#include <errno.h>
#include <string.h>

/**
 * Sets the error of an SSQ error struct.
 * @param err the SSQ error struct
 * @param code error code
 * @param message error message
 */
static inline void ssq_error_set(struct ssq_error *const err, const enum ssq_error_code code, const char message[])
{
    err->code = code;
    strncpy(err->message, message, SSQ_ERRMSG_SIZE);
}

/**
 * Sets the error of an SSQ error struct to the last system error.
 * @param err the SSQ error struct
 */
static inline void ssq_error_set_sys(struct ssq_error *const err)
{
    err->code = SSQ_ERR_SYS;

#ifdef _WIN32
    strerror_s(err->message, SSQ_ERRMSG_SIZE, errno);
#else
    strerror_r(errno, err->message, SSQ_ERRMSG_SIZE);
#endif
}

#ifdef _WIN32

#include <winsock2.h>

/**
 * Sets the error of an SSQ error struct to the last WSA error.
 * @param err the SSQ error struct
 */
static inline void ssq_error_set_wsa(struct ssq_error *const err)
{
    err->code = SSQ_ERR_SYS;

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        err->message,
        SSQ_ERRMSG_SIZE,
        NULL
    );
}

#endif

/**
 * Clears the error of an SSQ error struct.
 * @param err the SSQ error struct
 */
static inline void ssq_error_clear(struct ssq_error *const err)
{
    err->code = SSQ_OK;
    err->message[0] = '\0';
}

#endif /* SSQ_ERROPS_H */
