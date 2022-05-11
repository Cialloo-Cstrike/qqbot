#ifndef SSQ_A2S_PLAYER_H
#define SSQ_A2S_PLAYER_H

#include "ssq/ssq.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct a2s_player
{
    uint8_t index;    /** Index of player chunk starting from 0 */
    char   *name;     /** Name of the player */
    int32_t score;    /** Player's score (usually "frags" or "kills") */
    float   duration; /** Time (in seconds) player has been connected to the server */
};

/**
 * Sends an A2S_PLAYER query.
 * @param querier the Source server querier to use
 * @param player_count where to store the number of players in the response
 * @returns an array of A2S_PLAYER
 */
struct a2s_player *ssq_player(struct ssq_querier *querier, uint8_t *player_count);

/**
 * Frees an array of A2S_PLAYER.
 * @param players the A2S_PLAYER array to free
 * @param player_count number of players in the A2S_PLAYER array
 */
void ssq_player_free(struct a2s_player *players, uint8_t player_count);

#ifdef __cplusplus
}
#endif

#endif /* SSQ_A2S_PLAYER_H */
