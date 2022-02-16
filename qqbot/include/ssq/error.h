#ifndef SSQ_ERROR_H
#define SSQ_ERROR_H

#define SSQ_ERRMSG_SIZE 512

#ifdef __cplusplus
extern "C"
{
#endif

enum ssq_error_code
{
    SSQ_OK,             /* no error     */
    SSQ_ERR_SYS,        /* system error */
    SSQ_ERR_BADRES,     /* bad response */
    SSQ_ERR_UNSUPPORTED /* unsupported feature */
};

struct ssq_error
{
    /** error code */
    enum ssq_error_code code;

    /** error message */
    char message[SSQ_ERRMSG_SIZE];
};

#ifdef __cplusplus
}
#endif

#endif /* SSQ_ERROR_H */
