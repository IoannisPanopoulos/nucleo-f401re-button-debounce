#include "debounce.h"

static uint8_t pressed_from_raw(uint8_t raw, uint8_t active_high) {
    return active_high ? (raw ? 1u : 0u) : (raw ? 0u : 1u);
}

void debounce_init(debounce_t *d, uint32_t debounce_ms, uint8_t active_high) {
    if (!d) return;
    d->debounce_ms = debounce_ms;
    d->active_high = active_high ? 1u : 0u;
    d->stable_raw = 0u;
    d->last_raw = 0u;
    d->last_change_ms = 0u;
    d->initialized = 0u;
}

db_event_t debounce_update(debounce_t *d, uint8_t raw, uint32_t now_ms) {
    if (!d) return DB_EVENT_NONE;
    raw = raw ? 1u : 0u;

    if (!d->initialized) {
        d->stable_raw = raw;
        d->last_raw = raw;
        d->last_change_ms = now_ms;
        d->initialized = 1u;
        return DB_EVENT_NONE;
    }

    if (raw != d->last_raw) {
        d->last_raw = raw;
        d->last_change_ms = now_ms;
    }

    if (d->stable_raw != d->last_raw) {
        uint32_t dt = now_ms - d->last_change_ms; // handles wrap naturally for unsigned
        if (dt >= d->debounce_ms) {
            uint8_t old_pressed = pressed_from_raw(d->stable_raw, d->active_high);
            d->stable_raw = d->last_raw;
            uint8_t new_pressed = pressed_from_raw(d->stable_raw, d->active_high);

            if (old_pressed != new_pressed) {
                return new_pressed ? DB_EVENT_PRESSED : DB_EVENT_RELEASED;
            }
        }
    }

    return DB_EVENT_NONE;
}

uint8_t debounce_is_pressed(const debounce_t *d) {
    if (!d || !d->initialized) return 0u;
    return pressed_from_raw(d->stable_raw, d->active_high);
}
