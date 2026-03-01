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
    uint32_t debounce_ms;      
    uint8_t  active_high;      
    uint8_t  stable_raw;       
    uint8_t  last_raw;        
    uint32_t last_change_ms;   
    uint8_t  initialized;      
} debounce_t;


void debounce_init(debounce_t *d, uint32_t debounce_ms, uint8_t active_high);

// Returns an event when the *stable pressed state* changes.
db_event_t debounce_update(debounce_t *d, uint8_t raw, uint32_t now_ms);

// Returns 1 if the debounced state is pressed.
uint8_t debounce_is_pressed(const debounce_t *d);

#ifdef __cplusplus
}
#endif
