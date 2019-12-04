/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#ifndef __DISPLAY__
#define __DISPLAY__

/**
 * Uses a SSD1803A based LCD display that is connected via SPI.
 */
class Display {
private:
    int csPin;
    int resetPin;

    /**
     * Opens the connection to the display.
     *
     * There is no check whether SPI is currently in use!
     */
    void open() const;

    /**
     * Closes the connection to the display.
     */
    void close() const;

    /**
     * Busy waits for the display operation to complete.
     */
    void wait() const;

    /**
     * Sends a command to the display.
     *
     * @param cmd       Command to send
     */
    void sendCommand(char cmd) const;

    /**
     * Sends a character to the display.
     *
     * @param chr       Character to send
     */
    void sendChar(char chr) const;

public:
    /**
     * Creates a new Display object.
     *
     * The display is _not_ reset automatically.
     *
     * @param csPin     Pin number of the display's Chip Select input
     * @param resetPin  Pin number of the display's Reset input
     */
    Display (int csPin, int resetPin);

    /**
     * Resets the display.
     */
    void reset() const;

    /**
     * Turns display to sleep mode. It is turned off and put in a low-power state.
     */
    void sleep() const;

    /**
     * Wakes up display that is in sleep mode.
     */
    void wakeup() const;

    /**
     * Prints a text.
     *
     * @param row       Display row
     * @param text      Text to print
     */
    void print(int row, char *text) const;

    /**
     * Renders a bargraph.
     *
     * @param row       Display row
     * @param percent   Bargraph value (0..100)
     */
    void bargraph(int row, int percent) const;

    /**
     * Renders a balance.
     *
     * @param row       Display row
     * @param percent   Balance value (-100..100)
     */
    void balance(int row, int percent) const;

};

#endif
