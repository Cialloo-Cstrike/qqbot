#ifndef SSQ_A2S_RULES_H
#define SSQ_A2S_RULES_H

#include "ssq/ssq.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct a2s_rules
{
    char *name;  /** Name of the rule */
    char *value; /** Value of the rule */
};

/**
 * Sends an A2S_RULES query.
 * @param querier the Source server querier to use
 * @param rule_count where to store the number of rules in the response
 * @returns an array of A2S_RULES
 */
struct a2s_rules *ssq_rules(struct ssq_querier *querier, uint16_t *rule_count);

/**
 * Frees an array of A2S_RULES.
 * @param rules the A2S_RULES array to free
 * @param rule_count number of rules in the A2S_RULES array
 */
void ssq_rules_free(struct a2s_rules *rules, uint16_t rule_count);

#ifdef __cplusplus
}
#endif

#endif /* SSQ_A2S_RULES_H */
