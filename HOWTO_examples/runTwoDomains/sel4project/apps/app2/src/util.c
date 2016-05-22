/* Include Kconfig variables. */
#include <autoconf.h>

#include <sel4/sel4.h>

/* avoid main falling off the end of the world */
void abort(void) {
    while (1);
}

/* allow printf to use kernel debug printing */
void __arch_putchar(int c) {
#ifdef CONFIG_DEBUG_BUILD
    seL4_DebugPutChar(c);
#endif
}


