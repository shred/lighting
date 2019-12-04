/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#include <MD_REncoder.h>
#include <SPI.h>

#include "Config.h"
#include "Display.h"
#include "Menu.h"
#include "Effect.h"
#include "Strip.h"


#define DEBOUNCE_MS 100         // debounce time

#define DISPLAY_FADE_AFTER 10000 // Display fade starts after ms
#define DISPLAY_FADE_STEP 2     // Display fade step
#define DISPLAY_FADE_RATE 20    // Display fade rate in ms

#define LED_COUNT 104           // <---- Number of LEDs, CHANGE HERE ----

#define LED_PIN   19            // A5: NeoPixel Strip

#define POWER_BUTTON_PIN 6      //  6: Power Button
#define MENU_BUTTON_PIN 11      // 11: Menu Button
#define POWER_LED_PIN 18        // A4: Power LED

#define ROTARY_BUTTON_PIN 12    // 12: Rotary Button
#define ROTARY_A_PIN 9          //  9: Rotary Pin A
#define ROTARY_B_PIN 10         // 10: Rotary Pin B
#define ENABLE_SPEED 0          // Do not measure rotary speed

#define DISPLAY_RESET_PIN 14    // A0: Display Reset
#define DISPLAY_CS_PIN 15       // A1: Display CS
#define DISPLAY_LIGHT_PIN 5     //  5: Display LED


Config config {};

Strip strip(LED_PIN, LED_COUNT, config);
Display display(DISPLAY_CS_PIN, DISPLAY_RESET_PIN);
MD_REncoder rotary(ROTARY_A_PIN, ROTARY_B_PIN);

Menu *menuList[] = {
    new MenuBrightness(),
    new MenuEffect(),
    new MenuSaturation(),
    new MenuTemperature()
};

Effect *effectList[] = {
    new EffectNightshift(strip, config),
    new EffectJustWhite(strip, config),
    new EffectRainbow(strip, config),
    new EffectStarlight(strip, config)
};

int displayBrightness;
unsigned long displayNextTime;


/**
 * Waits until all buttons have been released. After that, a delay of DEBOUNCE_MS is added
 * to debounce the key.
 */
void waitUntilButtonsReleased() {
    while (digitalRead(POWER_BUTTON_PIN) == LOW
          || digitalRead(MENU_BUTTON_PIN) == LOW
          || digitalRead(ROTARY_BUTTON_PIN) == LOW) {
        // busy wait for buttons to be released
    }
    delay(DEBOUNCE_MS); // debounce key
}

/**
 * Activates the currently selected menu.
 */
void activateMenu() {
    config.menus[config.currentMenu]->activate(config);
    config.menus[config.currentMenu]->render(display);
}

/**
 * Applies the currently selected effect to the LED strip.
 */
void applyEffect() {
    config.effects[config.currentEffect]->apply();
}

/**
 * Turns the lighting off. The strip is turned black and the LCD is turned off.
 * The power LED is turned on, and then a busy wait loop waits for the power button to be
 * pressed again. After that, the LCD is turned on and the current effect is applied to
 * the LED strip.
 */
void powerOff() {
    // Turn power LED on
    digitalWrite(POWER_LED_PIN, HIGH);

    // Turn display LED off
    displayLightOff();

    // Turn LED strip off
    strip.black();

    // Turn display off
    display.sleep();

    // Wait for all buttons to be released
    waitUntilButtonsReleased();

    // Wait for the power button to be pressed
    while (digitalRead(POWER_BUTTON_PIN) == HIGH) {
        // busy wait
    }
    delay(DEBOUNCE_MS);

    // Turn power LED off
    digitalWrite(POWER_LED_PIN, LOW);

    // Turn display on
    display.wakeup();

    // Turn on LED strip
    applyEffect();
}

/**
 * Checks if the display backlight needs to be faded out, and fades accordingly.
 *
 * @return true if the display fadeout has just been completed. This can be used to reset
 * to a standard menu when the display fader timed out.
 */
boolean displayLightCheck() {
    if (displayNextTime != 0 && displayNextTime <= millis()) {
        displayBrightness -= DISPLAY_FADE_STEP;
        if (displayBrightness > 0 && displayBrightness < 256) {
            analogWrite(DISPLAY_LIGHT_PIN, displayBrightness);
            displayNextTime += DISPLAY_FADE_RATE;
        } else if (displayBrightness <= 0) {
            analogWrite(DISPLAY_LIGHT_PIN, 0);
            displayNextTime = 0;
            return true;
        }
    }
    return false;
}

/**
 * Turns the display backlight on. After a while, the backlight will fade out
 * automatically. This function can be invoked multiple times, to retrigger the backlight
 * fade timeout.
 */
void displayLightOn() {
    analogWrite(DISPLAY_LIGHT_PIN, 255);
    displayBrightness = 255;
    displayNextTime = millis() + DISPLAY_FADE_AFTER;
}

/**
 * Turns the display backlight off immediately.
 */
void displayLightOff() {
    analogWrite(DISPLAY_LIGHT_PIN, 0);
    displayNextTime = 0;
}

/**
 * Sets up the sheet.
 */
void setup() {
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
        clock_prescale_set(clock_div_1);
    #endif

    pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);
    pinMode(MENU_BUTTON_PIN, INPUT_PULLUP);
    pinMode(POWER_LED_PIN, OUTPUT);
    pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP);
    pinMode(DISPLAY_LIGHT_PIN, OUTPUT);

    SPI.begin();
    rotary.begin();
    display.reset();

    config.menus = menuList;
    config.menuCount = sizeof(menuList) / sizeof(menuList[0]);

    config.effects = effectList;
    config.effectCount = sizeof(effectList) / sizeof(effectList[0]);
    config.currentEffect = 0;

    displayLightOff();

    activateMenu();
    applyEffect();
    displayLightOn();
}

/**
 * Main loop.
 */
void loop() {
    uint8_t rotChange = rotary.read();
    if (rotChange != DIR_NONE) {
        config.menus[config.currentMenu]->change(rotChange == DIR_CW ? 1 : -1);
        config.menus[config.currentMenu]->render(display);
        displayLightOn();
    }

    if (digitalRead(POWER_BUTTON_PIN) == LOW) {
        powerOff();
        displayLightOn();
        waitUntilButtonsReleased();
    }

    if (digitalRead(MENU_BUTTON_PIN) == LOW) {
        config.currentMenu++;
        if (config.currentMenu >= config.menuCount) {
            config.currentMenu = 0;
        }
        activateMenu();
        displayLightOn();
        waitUntilButtonsReleased();
    }

    if (digitalRead(ROTARY_BUTTON_PIN) == LOW) {
        config.menus[config.currentMenu]->apply(config);
        applyEffect();
        config.currentMenu = 0;
        activateMenu();
        displayLightOn();
        waitUntilButtonsReleased();
    }

    if (displayLightCheck()) {
        config.currentMenu = 0;
        activateMenu();
    };
}
