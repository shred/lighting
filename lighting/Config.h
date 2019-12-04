/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#ifndef __AL_CONFIG__
#define __AL_CONFIG__

class Menu;
class Effect;

typedef struct {
    int currentEffect = 0;
    int currentMenu = 0;
    int brightness = 50;
    int saturation = 100;
    int temperature = 0;
    Menu **menus;
    int menuCount;
    Effect **effects;
    int effectCount;
} Config;

#endif
