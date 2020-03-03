#ifndef EMPR_FLAGRECOGNISER_H_
#define EMPR_FLAGRECOGNISER_H_

#include <stdint.h>


typedef enum {
    UNITED_KINGDOM = 0,
    FRANCE,
    SYRIA,
    ICELAND,
    SUDAN,
    NORTH_MACEDONIA,
    CZECHIA,
    BURKINA_FASO,
    CENTRAL_AFRICAN_REBUBLIC,
    BURUNDI
} FlagId;

#define FIRST_FLAG UNITED_KINGDOM
#define LAST_FLAG BURUNDI
#define FLAG_COUNT (LAST_FLAG - FIRST_FLAG + 1)

typedef uint32_t (*ErrorFunction)(FlagId);
typedef void (*DataGatherFunction)(void);

FlagId FlagRecogniser_run(DataGatherFunction dataGatherFunc, ErrorFunction errorFunc);


#endif // EMPR_FLAGRECOGNISER_H_
