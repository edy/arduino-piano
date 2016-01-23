#include "melodies.h"
#include "led.h"
#include "button.h"
#include "pins.h"

int tones[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};

byte previousPushedButtons = 0;

void setup() {
    pinMode(BUTTONS_ENABLE_PIN, OUTPUT);
    pinMode(BUTTONS_LOAD_PIN, OUTPUT);
    pinMode(BUTTONS_CLOCK_PIN, OUTPUT);
    pinMode(BUTTONS_DATA_PIN, INPUT);

    //set pins to output so you can control the shift register
    pinMode(LEDS_LATCH_PIN, OUTPUT);
    pinMode(LEDS_CLOCK_PIN, OUTPUT);
    pinMode(LEDS_DATA_PIN, OUTPUT);

    // Required initial states of these two pins according to the datasheet timing diagram
    digitalWrite(BUTTONS_LOAD_PIN, HIGH);
    digitalWrite(BUTTONS_ENABLE_PIN, HIGH);

    Serial.begin(9600);

    showNumber(LED_ALL);
    delay(200);
    showNumber(LED_OFF);
    delay(200);
    showNumber(LED_ALL);
    delay(200);
    showNumber(LED_OFF);

    playMelody(joy);
}

void loop() {
    byte buttonsPressed = getNumber();

    if (previousPushedButtons != buttonsPressed) {
        int number = log2(buttonsPressed);
        previousPushedButtons = buttonsPressed;

        showNumber(buttonsPressed);
        noTone(SPEAKER);

        if (number >= 0) {
            int tn = tones[number];
            tone(SPEAKER, tn);
        }
    }

    delay(50);
}

void playMelody (struct note melody[]) {
    int i = 0;
    while (true) {
        // melody has finished
        if (melody[i].height == 0 && melody[i].duration == 0) {
            break;
        }

        // calculae the playing time of a note
        int noteDuration = 1000 / melody[i].duration;

        // play a tone only if it's not a pause note
        if (melody[i].height > 0) {
            showNumber(melody[i].led);
            tone(SPEAKER, melody[i].height);
            delay(noteDuration);
            noTone(SPEAKER);
        } else {
            delay(noteDuration);
        }

        // turn off all leds
        showNumber(LED_OFF);

        // to distinguish the notes, set a minimum time between them.
        // 30% of the note's duration seems to work well:
        int pauseBetweenNotes = noteDuration * 0.20;
        delay(pauseBetweenNotes);

        i++;
    }
}

void showNumber (byte number) {
    // take the LEDS_LATCH_PIN low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(LEDS_LATCH_PIN, LOW);

    // shift out the bits:
    shiftOut(LEDS_DATA_PIN, LEDS_CLOCK_PIN, MSBFIRST, number);

    //take the latch pin high so the LEDs will light up:
    digitalWrite(LEDS_LATCH_PIN, HIGH);
}

byte getNumber () {
    digitalWrite(BUTTONS_LOAD_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(BUTTONS_LOAD_PIN, HIGH);
    delayMicroseconds(5);

    digitalWrite(BUTTONS_CLOCK_PIN, HIGH);
    digitalWrite(BUTTONS_ENABLE_PIN, LOW);

    byte incoming = shiftIn(BUTTONS_DATA_PIN, BUTTONS_CLOCK_PIN, MSBFIRST);

    digitalWrite(BUTTONS_ENABLE_PIN, HIGH);

    return incoming;
}

int log2 (byte number) {
    if ((int) number == 0) {
        return -1;
    }

    // https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious
    unsigned int v = (int) number; // 32-bit word to find the log base 2 of
    unsigned int r = 0; // r will be lg(v)

    while (v >>= 1) // unroll for more speed...
    {
        r++;
    }

    return r;
    //return (int) (log (number) / log (2)); // log_2 number
}
