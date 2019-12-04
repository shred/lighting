/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#ifndef __AL_MENU__
#define __AL_MENU__

#include "Config.h"
#include "Display.h"
#include "Effect.h"

/**
 * Abstract class definition for a menu.
 */
class Menu {
public:
    /**
     * Acivates the menu. It has been selected by the user. Now it should make a copy of
     * the desired Config parameters.
     * 
     * @param config    Config to copy the parameters from
     */
    virtual void activate(Config &config) = 0;

    /**
     * Renders the menu on the Display.
     * 
     * @param display   Display to render the current menu state to.
     */
    virtual void render(Display &display) = 0;

    /**
     * Changes the menu's value.
     * 
     * @param increment Increment to change the value with. May be positive or negative,
     * but is never 0.
     */
    virtual void change(int32_t increment) = 0;

    /**
     * Applies the changed value to the Config. The user has accepted the change.
     * 
     * @param config    Config to write the changed value into.
     */
    virtual void apply(Config &config) = 0;
};

/**
 * The brightness menu. This is the standard menu. It shows the name of the effect that is
 * currently selected, and offers to change the brightness.
 */
class MenuBrightness : public Menu {
private:
    int current;
    char *effectName;

public:
    virtual void activate(Config &config) override;
    virtual void render(Display &display) override;
    virtual void change(int32_t increment) override;
    virtual void apply(Config &config) override;
};

/**
 * The effect menu. The user can pick an effect from the available effects.
 */
class MenuEffect : public Menu {
private:
    int current;
    Effect **effects;
    int effectCount;

public:
    virtual void activate(Config &config) override;
    virtual void render(Display &display) override;
    virtual void change(int32_t increment) override;
    virtual void apply(Config &config) override;
};

/**
 * The saturation menu. The user changes the color saturation level.
 */
class MenuSaturation : public Menu {
private:
    int current;

public:
    virtual void activate(Config &config) override;
    virtual void render(Display &display) override;
    virtual void change(int32_t increment) override;
    virtual void apply(Config &config) override;
};

/**
 * The temperature menu. The user changes the desired color temperature of white.
 */
class MenuTemperature : public Menu {
private:
    int current;

public:
    virtual void activate(Config &config) override;
    virtual void render(Display &display) override;
    virtual void change(int32_t increment) override;
    virtual void apply(Config &config) override;
};

#endif
