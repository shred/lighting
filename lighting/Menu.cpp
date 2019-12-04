/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#include "Menu.h"


/*---- MenuBrightness ----*/

void MenuBrightness::activate(Config &config) {
    current = config.brightness;
    effectName = config.effects[config.currentEffect]->name();
}

void MenuBrightness::render(Display &display) {
    display.print(0, effectName);
    display.print(1, "");
    display.bargraph(2, this->current);
}

void MenuBrightness::change(int32_t increment) {
    this->current += increment * 5;
    if (this->current < 0) {
        this->current = 0;
    }
    if (this->current > 100) {
        this->current = 100;
    }
}

void MenuBrightness::apply(Config &config) {
    config.brightness = this->current;
}


/*---- MenuBrightness ----*/

void MenuEffect::activate(Config &config) {
    this->current = config.currentEffect;
    this->effects = config.effects;
    this->effectCount = config.effectCount;
}

void MenuEffect::render(Display &display) {
    display.print(0, "Effect");
    display.print(1, effects[current]->name());
    display.print(2, "");
}

void MenuEffect::change(int32_t increment) {
    current += increment;
    while (current < 0) {
        current += effectCount;
    }
    while (current > effectCount - 1) {
        current -= effectCount;
    }
}

void MenuEffect::apply(Config &config) {
    config.currentEffect = current;
}


/*---- MenuSaturation ----*/

void MenuSaturation::activate(Config &config) {
    this->current = config.saturation;
}

void MenuSaturation::render(Display &display) {
    display.print(0, "Saturation");
    display.bargraph(1, current);
    display.print(2, "");
}

void MenuSaturation::change(int32_t increment) {
    this->current += increment * 5;
    if (this->current < 0) {
        this->current = 0;
    }
    if (this->current > 100) {
        this->current = 100;
    }
}

void MenuSaturation::apply(Config &config) {
    config.saturation = current;
}


/*---- MenuTemperature ----*/

void MenuTemperature::activate(Config &config) {
    this->current = config.temperature;
}

void MenuTemperature::render(Display &display) {
    display.print(0, "Color Temp");
    display.balance(1, current);
    display.print(2, "\xE1" "cold hot" "\xDF");
}

void MenuTemperature::change(int32_t increment) {
    this->current += increment * 10;
    if (this->current > -10 && this->current < 10) {
        this->current = 0;
    }
    if (this->current < -100) {
        this->current = -100;
    }
    if (this->current > 100) {
        this->current = 100;
    }
}

void MenuTemperature::apply(Config &config) {
    config.temperature = current;
}
