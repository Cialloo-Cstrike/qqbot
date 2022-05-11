#ifndef SSQ_PACKET_H
#define SSQ_PACKET_H

#define A2S_PACKET_HEADER_SINGLE (-1)
#define A2S_PACKET_HEADER_MULTI  (-2)

#include "ssq/error.h"

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct ssq_packet
{
    int32_t header;  /** The packet's header */
    int32_t id;      /** Unique number assigned by server per answer */
    uint8_t total;   /** The total number of packets in the response */
    uint8_t number;  /** The number of the packet */
    size_t  size;    /** The size of the payload */
    char   *payload; /** The packet's payload */
};

/**
 * Deserializes a packet.
 * @param data raw packet data
 * @param size number of bytes in the raw packet data
 * @param err struct where to report potential errors
 */
struct ssq_packet *ssq_packet_init(const char data[], uint16_t size, struct ssq_error *err);

/**
 * Merges the payloads of many packets into a single response.
 * @param packets the array of packets
 * @param count number of packets
 * @param size where to store the size of the response
 * @param err where to report potential errors
 * @returns a dynamically-allocated concatenation of the packets' payloads
 */
char *ssq_packet_mergepayloads(struct ssq_packet *const *packets, uint8_t count, size_t *size, struct ssq_error *err);

/**
 * Frees a packet.
 * @param packet the packet to free
 */
void ssq_packet_free(struct ssq_packet *packet);

/**
 * Frees an array of packets.
 * @param packets the array of packets to free
 * @param packet_count number of packets
 */
void ssq_packet_freearr(struct ssq_packet **packets, uint8_t packet_count);

#ifdef __cplusplus
}
#endif

#endif /* SSQ_PACKET_H */
