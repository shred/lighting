/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#ifndef __AL_EFFECT__
#define __AL_EFFECT__

#include "Config.h"
#include "Strip.h"

/**
 * Abstract Effect class. Effects are color schemes that are applied to the LED strip.
 */
class Effect {
protected:
    Strip *strip;
    Config *config;

public:
    /**
     * Creates a new Effect instance.
     * 
     * @param strip     Strip to apply the effect on
     * @param config    Config containing parameters
     */
    Effect(Strip &strip, Config &config) {
        this->strip = &strip;
        this->config = &config;
    }

    /**
     * Returns the name of the effect. Must not be longer than 10 characters.
     */
    virtual char* name() const = 0;

    /**
     * Applies the effect.
     */
    virtual void apply() const = 0;
};


/**
 * Nightshift: My favorite personal color scheme. Mostly blue, but white behind my
 * monitors.
 */
class EffectNightshift : public Effect {
public:
    using Effect::Effect;

    virtual char* name() const override {
        return "Nightshift";
    }

    virtual void apply() const override;
};


/**
 * Just White: All LEDs in white, for maximum illumination.
 */
class EffectJustWhite : public Effect {
public:
    using Effect::Effect;

    virtual char* name() const override {
        return "Just White";
    }

    virtual void apply() const override;
};


/**
 * Rainbow: A rainbow color scheme.
 */
class EffectRainbow : public Effect {
public:
    using Effect::Effect;

    virtual char* name() const override {
        return "Rainbow";
    }

    virtual void apply() const override;
};


/**
 * Starlight: Night blue, with random white stars.
 */
class EffectStarlight : public Effect {
public:
    using Effect::Effect;

    virtual char* name() const override {
        return "Starlight";
    }

    virtual void apply() const override;
};

#endif
