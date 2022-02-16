#ifndef SSQ_BUFFER_H
#define SSQ_BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct ssq_buf
{
    const char *data;
    size_t      pos;
    size_t      size;
};

/**
 * Gets the cursor position of a buffer.
 * @param buf the buffer
 * @returns cursor position of the buffer
 */
static inline size_t ssq_buf_pos(const struct ssq_buf *const buf)
{
    return buf->pos;
}

/**
 * Determines if the end of the buffer was reached.
 * @param buf the buffer
 * @returns true if the end of the buffer was reached
 */
static inline bool ssq_buf_eob(const struct ssq_buf *const buf)
{
    return buf->pos >= buf->size;
}

/**
 * Forwards N bytes into the buffer.
 * @param buf the buffer
 * @param n number of bytes
 */
static inline void ssq_buf_forward(struct ssq_buf *const buf, const size_t n)
{
    buf->pos += n;
}

/**
 * Initializes a buffer.
 * @param buf the buffer
 * @param data address of the data to use
 * @param size size of the data in bytes
 */
void ssq_buf_init(struct ssq_buf *buf, const void *data, size_t size);

/**
 * Reads N bytes of data from the buffer into a destination memory space.
 * @param buf the buffer
 * @param dst where to copy the data
 * @param n number of bytes to copy
 */
void ssq_buf_read(struct ssq_buf *buf, void *dst, size_t n);

/**
 * Reads an 8-bit signed integer from a buffer.
 * @param buf the buffer
 * @returns the 8-bit signed integer at the current position
 */
int8_t ssq_buf_read_int8(struct ssq_buf *buf);

/**
 * Reads a 16-bit signed integer from a buffer.
 * @param buf the buffer
 * @returns the 16-bit signed integer at the current position
 */
int16_t ssq_buf_read_int16(struct ssq_buf *buf);

/**
 * Reads a 32-bit signed integer from a buffer.
 * @param buf the buffer
 * @returns the 32-bit signed integer at the current position
 */
int32_t ssq_buf_read_int32(struct ssq_buf *buf);

/**
 * Reads a 64-bit signed integer from a buffer.
 * @param buf the buffer
 * @returns the 64-bit signed integer at the current position
 */
int64_t ssq_buf_read_int64(struct ssq_buf *buf);

/**
 * Reads an 8-bit unsigned integer from a buffer.
 * @param buf the buffer
 * @returns the 8-bit unsigned integer at the current position
 */
uint8_t ssq_buf_read_uint8(struct ssq_buf *buf);

/**
 * Reads a 16-bit unsigned integer from a buffer.
 * @param buf the buffer
 * @returns the 16-bit unsigned integer at the current position
 */
uint16_t ssq_buf_read_uint16(struct ssq_buf *buf);

/**
 * Reads a 32-bit unsigned integer from a buffer.
 * @param buf the buffer
 * @returns the 32-bit unsigned integer at the current position
 */
uint32_t ssq_buf_read_uint32(struct ssq_buf *buf);

/**
 * Reads a 64-bit unsigned integer from a buffer.
 * @param buf the buffer
 * @returns the 64-bit unsigned integer at the current position
 */
uint64_t ssq_buf_read_uint64(struct ssq_buf *buf);

/**
 * Reads a float from a buffer.
 * @param buf the buffer
 * @returns the float at the current position
 */
float ssq_buf_read_float(struct ssq_buf *buf);

/**
 * Reads a double from a buffer.
 * @param buf the buffer
 * @returns the double at the current position
 */
double ssq_buf_read_double(struct ssq_buf *buf);

/**
 * Reads a long double from a buffer.
 * @param buf the buffer
 * @returns the long double at the current position
 */
long double ssq_buf_read_longdouble(struct ssq_buf *buf);

/**
 * Reads a boolean from a buffer.
 * @param buf the buffer
 * @returns the boolean at the current position
 */
bool ssq_buf_read_bool(struct ssq_buf *buf);

/**
 * Reads a null-terminated string from a buffer.
 * @param buf the buffer
 * @returns a dynamically-allocated copy of the string at the current position
 */
char *ssq_buf_read_string(struct ssq_buf *buf);

#ifdef __cplusplus
}
#endif

#endif /* SSQ_BUFFER_H */
