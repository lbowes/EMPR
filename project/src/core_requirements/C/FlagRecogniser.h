#ifndef EMPR_FLAGRECOGNISER_H_
#define EMPR_FLAGRECOGNISER_H_

#include <stdint.h>


typedef enum {
    BRITAIN = 0,
    FRANCE,
    ITALY
} FlagId;

#define FLAG_COUNT (ITALY - BRITAIN + 1)

typedef uint32_t (*ErrorFunction)(FlagId);


FlagId FlagRecogniser_run(ErrorFunction errorFunc);


#endif // EMPR_FLAGRECOGNISER_H_
