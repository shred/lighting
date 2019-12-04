/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#include "Strip.h"

/**
 * Converts the given float to an unsigned integer that is guaranteed to be between
 * 0 and 255.
 * 
 * @param val       Float value to convert
 * @return integer value, guaranteed to be between 0 and 255. Exceeding values are
 * clipped.
 */
static uint8_t limit(float val) {
    if (val < 0.0) {
        val = 0.0;
    }
    if (val > 255.0) {
        val = 255.0;
    }
    return (uint8_t) val;
}

Strip::Strip(uint8_t pin, uint16_t length, Config &config) {
    this->config = &config;
    this->strip = new Adafruit_NeoPixel(length, pin, NEO_GRBW + NEO_KHZ800);
    strip->begin();
    strip->setBrightness(255);
    strip->fill(0x00000000);
    strip->show();
}

int Strip::count() const {
    return strip->numPixels();
}

void Strip::black() const {
    strip->fill(0x00000000);
    strip->show();
}

void Strip::set(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b, uint8_t w) const {
    strip->setPixelColor(
        pixel,
        cr(r, g, b, w),
        cg(r, g, b, w),
        cb(r, g, b, w),
        cw(r, g, b, w)
    );
}

void Strip::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const {
    strip->fill(Adafruit_NeoPixel::Color(
        cr(r, g, b, w),
        cg(r, g, b, w),
        cb(r, g, b, w),
        cw(r, g, b, w)
    ));
}

void Strip::show() const {
    strip->show();
}

uint8_t Strip::cr(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const {
    float v = r * (config->brightness / 100.0) * (config->saturation / 100.0);
    if (config->temperature > 0) {
        v += w * config->temperature / 200.0;
    }
    return limit(v);
}

uint8_t Strip::cg(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const {
    float v = g * (config->brightness / 100.0) * (config->saturation / 100.0);
    if (config->temperature > 0) {
        v += w * config->temperature / 400.0;
    }
    return limit(v);
}

uint8_t Strip::cb(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const {
    float v = b * (config->brightness / 100.0) * (config->saturation / 100.0);
    if (config->temperature < 0) {
        v += w * -config->temperature / 600.0;
    }
    return limit(v);
}

uint8_t Strip::cw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) const {
    int temp = config->temperature >= 0 ? config->temperature : -config->temperature;

    float v = w * (config->brightness / 100.0);
    v += ((r + g + b) / 3.0) * ((100 - config->saturation) / 100.0);
    v -= w * temp / 600.0;
    return limit(v);
}
