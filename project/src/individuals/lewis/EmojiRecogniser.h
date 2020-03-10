#ifndef EMPR_EMOJI_RECOGNISER_H_
#define EMPR_EMOJI_RECOGNISER_H_

#include <stdint.h>


typedef enum {
    CRYING_LAUGHTER = 0,
    HEART_EYES,
    POOL_OF_TEARS,
    RED_CHEEKS,
    SAD,
    SHADES,
    SMILE,
    SMILING_PILE_OF_POO,
    TEETH,
    THINKING
} EmojiId;

#define FIRST_EMOJI CRYING_LAUGHTER
#define LAST_EMOJI THINKING
#define EMOJI_COUNT (LAST_EMOJI - FIRST_EMOJI + 1)

typedef enum {
    UP = 0,
    LEFT,
    DOWN,
    RIGHT
} Orientation;

#define FIRST_ORIENTATION UP
#define LAST_ORIENTATION RIGHT
#define ORIENTATION_COUNT (FIRST_ORIENTATION - LAST_ORIENTATION + 1)

typedef uint32_t (*ErrorFunction)(EmojiId);
typedef void (*DataGatherFunction)(void);

void EmojiRecogniser_init();
void EmojiRecogniser_gatherData();
uint32_t EmojiRecogniser_errorFunc(EmojiId flagId);


#endif // EMPR_EMOJI_RECOGNISER_H_
