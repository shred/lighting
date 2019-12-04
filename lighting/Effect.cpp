/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#include "Effect.h"


/*---- EffectNightshift ----*/

void EffectNightshift::apply() const {
    for (int i = 0; i < strip->count(); i++) {
        if (i < 33 || (i >= 63 && i <= 70) || i > 90) {
            strip->set(i, 0, 0, 64, 0);
        } else {
            strip->set(i, 0, 0, 0, 255);
        }
    }
    strip->show();
}


/*---- EffectJustWhite ----*/

void EffectJustWhite::apply() const {
    strip->fill(0, 0, 0, 255);
    strip->show();
}


/*---- EffectRainbow ----*/

void EffectRainbow::apply() const {
    for (int i = 0; i < strip->count(); i++) {
        int pos = i * 256 / strip->count();
        if (pos < 85) {
            strip->set(i, 255 - pos * 3, pos * 3, 0, 0);
        } else if (pos < 170) {
            strip->set(i, 0, 255 - (pos - 85) * 3, (pos - 85) * 3, 0);
        } else {
            strip->set(i, (pos - 170) * 3, 0, 255 - (pos - 170) * 3, 0);
        }
    }
    strip->show();
}


/*---- EffectStarlight ----*/

void EffectStarlight::apply() const {
    for (int i = 0; i < strip->count(); i++) {
        if ((random(strip->count()) % 6) == 0) {
            strip->set(i, 0, 0, 0, 255);
        } else {
            strip->set(i, 0, 0, 20, 0);
        }
    }
    strip->show();
}
