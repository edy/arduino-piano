#include <stdint.h>
#include <stdlib.h>
#include "led.h"
#include "pitches.h"

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

#define PAUSE_4 {0, 4, LED_OFF}
#define PAUSE_8 {0, 8, LED_OFF}

struct note { uint16_t height; uint8_t duration; uint8_t led;};

static struct note alle_meine_entchen[] = {
    {NOTE_C4, 4, LED_1},
    {NOTE_D4, 4, LED_2},
    {NOTE_E4, 4, LED_3},
    {NOTE_F4, 4, LED_4},
    {NOTE_G4, 2, LED_5},
    {NOTE_G4, 2, LED_5},
    {NOTE_A4, 4, LED_6},
    {NOTE_A4, 4, LED_6},
    {NOTE_A4, 4, LED_6},
    {NOTE_A4, 4, LED_6},
    {NOTE_G4, 2, LED_5},
    PAUSE_8,
    {NOTE_A4, 4, LED_6},
    {NOTE_A4, 4, LED_6},
    {NOTE_A4, 4, LED_6},
    {NOTE_A4, 4, LED_6},
    {NOTE_G4, 2, LED_5},
    PAUSE_8,
    {NOTE_F4, 4, LED_4},
    {NOTE_F4, 4, LED_4},
    {NOTE_F4, 4, LED_4},
    {NOTE_F4, 4, LED_4},
    {NOTE_E4, 2, LED_3},
    {NOTE_E4, 2, LED_3},
    {NOTE_D4, 4, LED_2},
    {NOTE_D4, 4, LED_2},
    {NOTE_D4, 4, LED_2},
    {NOTE_D4, 4, LED_2},
    {NOTE_C4, 2, LED_1},
    {0, 0}
};

static struct note finish[] = {
    {NOTE_C5, 4, LED_8},
    {NOTE_G4, 8, LED_5},
    {NOTE_G4, 8, LED_5},
    {NOTE_A4, 4, LED_6},
    {NOTE_G4, 4, LED_5},
    PAUSE_4,
    {NOTE_B4, 4, LED_7},
    {NOTE_C5, 4, LED_8},
    {0, 0}
};

static struct note joy[] = {
    {NOTE_E4, 4, LED_3},
    {NOTE_E4, 4, LED_3},
    {NOTE_F4, 4, LED_4},
    {NOTE_G4, 4, LED_5},
    {NOTE_G4, 4, LED_5},
    {NOTE_F4, 4, LED_4},
    {NOTE_E4, 4, LED_3},
    {NOTE_D4, 4, LED_2},
    {NOTE_C4, 4, LED_1},
    {NOTE_C4, 4, LED_1},
    {NOTE_D4, 4, LED_2},
    {NOTE_E4, 4, LED_3},
    {NOTE_E4, 2, LED_3},
    {NOTE_D4, 8, LED_2},
    {NOTE_D4, 2, LED_2},
    PAUSE_8,
    {NOTE_E4, 4, LED_3},
    {NOTE_E4, 4, LED_3},
    {NOTE_F4, 4, LED_4},
    {NOTE_G4, 4, LED_5},
    {NOTE_G4, 4, LED_5},
    {NOTE_F4, 4, LED_4},
    {NOTE_E4, 4, LED_3},
    {NOTE_D4, 4, LED_2},
    {NOTE_C4, 4, LED_1},
    {NOTE_C4, 4, LED_1},
    {NOTE_D4, 4, LED_2},
    {NOTE_E4, 4, LED_3},
    {NOTE_D4, 2, LED_2},
    {NOTE_C4, 8, LED_1},
    {NOTE_C4, 2, LED_1},
    {0,  0}
};
