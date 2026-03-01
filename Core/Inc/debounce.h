#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DB_EVENT_NONE = 0,
    DB_EVENT_PRESSED = 1,
    DB_EVENT_RELEASED = 2
} db_event_t;

typedef struct {
    uint32_t debounce_ms;      // stable time required
    uint8_t  active_high;      // 1: pressed=1, 0: pressed=0
    uint8_t  stable_raw;       // last stable raw level (0/1)
    uint8_t  last_raw;         // last observed raw level (0/1)
    uint32_t last_change_ms;   // last time raw changed
    uint8_t  initialized;      // internal
} debounce_t;

// active_high:
//   1 -> raw=1 means "pressed"
//   0 -> raw=0 means "pressed"
void debounce_init(debounce_t *d, uint32_t debounce_ms, uint8_t active_high);

// Call whenever you sample the pin (polling or in an IRQ).
// Returns an event when the *stable pressed state* changes.
db_event_t debounce_update(debounce_t *d, uint8_t raw, uint32_t now_ms);

// Returns 1 if the debounced state is pressed.
uint8_t debounce_is_pressed(const debounce_t *d);

#ifdef __cplusplus
}
#endif
