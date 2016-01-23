#include <Arduino.h>
#include "pins.h"
#include "led.h"

void enableLED (int led) {
    // take the LEDS_LATCH_PIN low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(LEDS_LATCH_PIN, LOW);

    // shift out the bits:
    shiftOut(LEDS_DATA_PIN, LEDS_CLOCK_PIN, MSBFIRST, led);

    //take the latch pin high so the LEDs will light up:
    digitalWrite(LEDS_LATCH_PIN, HIGH);
}
