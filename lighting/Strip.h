/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#ifndef __AL_STRIP__
#define __AL_STRIP__

#include <Adafruit_NeoPixel.h>

#include "Config.h"

/**
 * Connects to a NeoPixel strip.
 */
class Strip {
private:
    Adafruit_NeoPixel* strip;
    Config* config;

    /**
     * Computes the red level. Configuration parameters like brightness, saturation, or
     * color temperature are considered.
     * 
     * @param r     Desired red level (0..255, truncated if range is exceeded)
     * @param g     Desired green level (0..255, truncated if range is exceeded)
     * @param b     Desired blue level (0..255, truncated if range is exceeded)
     * @param w     Desired white level (0..255, truncated if range is exceeded)
     */
    uint8_t cr(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const;

    /**
     * Computes the green level. Configuration parameters like brightness, saturation, or
     * color temperature are considered.
     * 
     * @param r     Desired red level (0..255, truncated if range is exceeded)
     * @param g     Desired green level (0..255, truncated if range is exceeded)
     * @param b     Desired blue level (0..255, truncated if range is exceeded)
     * @param w     Desired white level (0..255, truncated if range is exceeded)
     */
    uint8_t cg(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const;

    /**
     * Computes the blue level. Configuration parameters like brightness, saturation, or
     * color temperature are considered.
     * 
     * @param r     Desired red level (0..255, truncated if range is exceeded)
     * @param g     Desired green level (0..255, truncated if range is exceeded)
     * @param b     Desired blue level (0..255, truncated if range is exceeded)
     * @param w     Desired white level (0..255, truncated if range is exceeded)
     */
    uint8_t cb(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const;

    /**
     * Computes the white level. Configuration parameters like brightness, saturation, or
     * color temperature are considered.
     * 
     * @param r     Desired red level (0..255, truncated if range is exceeded)
     * @param g     Desired green level (0..255, truncated if range is exceeded)
     * @param b     Desired blue level (0..255, truncated if range is exceeded)
     * @param w     Desired white level (0..255, truncated if range is exceeded)
     */
    uint8_t cw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const;

public:
    /**
     * Creates a new Strip object.
     * 
     * @param pin       Pin number the NeoPixels are connected to
     * @param length    Number of NeoPixel LEDs in the strip
     * @param config    Config to be used
     */
    Strip(uint8_t pin, uint16_t length, Config &config);

    /**
     * Returns the number of LEDs in the strip.
     */
    int count() const;

    /**
     * Turns off all LEDs of the strip.
     */
    void black() const;

    /**
     * Sets an individual LED.
     * 
     * @param pixel     LED number to set
     * @param r         Red color value (0..255, truncated if range is exceeded)
     * @param g         Green color value (0..255, truncated if range is exceeded)
     * @param b         Blue color value (0..255, truncated if range is exceeded)
     * @param w         White color value (0..255, truncated if range is exceeded)
     */
    void set(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b, uint8_t w) const;

    /**
     * Fills the LED strip with the given color.
     * 
     * @param r         Red color value (0..255, truncated if range is exceeded)
     * @param g         Green color value (0..255, truncated if range is exceeded)
     * @param b         Blue color value (0..255, truncated if range is exceeded)
     * @param w         White color value (0..255, truncated if range is exceeded)
     */
    void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const;

    /**
     * Sends the color changes to the LED strip.
     */
    void show() const;

};

#endif
