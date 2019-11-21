#include <common_utils/TextOutput.h>
#include <common_utils/Interrupts.h>


Interrupts_handleAll() { }


int main(void) {
    TextOutput_init();
    TextOutput_printInteger(2134345);

    return 0;
}
