/*
 * Bias Lighting
 *
 * Copyright (C) 2019 Richard "Shred" Körber
 *   https://github.com/shred/lighting
 *
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike
 * license: https://creativecommons.org/licenses/by-nc-sa/4.0/
 */

#include "Display.h"

#include <Arduino.h>
#include <SPI.h>

#define RESET_TIME_MS 50        // reset signal is 50 ms
#define BITRATE 1000000         // max bitrate is 1 MHz

Display::Display (int csPin, int resetPin) {
    this->csPin = csPin;
    this->resetPin = resetPin;

    pinMode(this->resetPin, OUTPUT);
    pinMode(this->csPin, OUTPUT);
    digitalWrite(this->resetPin, HIGH);
    digitalWrite(this->csPin, HIGH);
}

void Display::reset() const {
    digitalWrite(resetPin, LOW);
    delay(RESET_TIME_MS);
    digitalWrite(resetPin, HIGH);
    delay(RESET_TIME_MS);

    open();
    sendCommand(0x3A);  // FS: IS=0 RE=1, 8 bit, 4 lines
    sendCommand(0x09);  // 5 pixel width, no inversion, 4 line mode
    sendCommand(0x06);  // Normal order, Reverse segment direction
    sendCommand(0x1E);  // 1/6 bias
    sendCommand(0x39);  // FS: IS=1 RE=0, 8 bit, 4 lines
    sendCommand(0x1B);  // Divider 540kHz (POR), 1/6 bias
    sendCommand(0x7A);  // Contrast 0x.A
    sendCommand(0x56);  // Contrast 0x2A, ICONs off, DC/DC on
    sendCommand(0x6E);  // Divider on, IR6 (1+Rb/Ra = 5.3)
    sendCommand(0x38);  // FS: IS=0 RE=0, 8 bit, 4 lines, double height font
    sendCommand(0x01);  // Clear Display
    sendCommand(0x0C);  // Display on, Cursor off, Cursor blink off
    sendCommand(0x3A);  // FS: IS=0 RE=1, 8 bit, 4 lines
    sendCommand(0x17);  // Display: 3 lines, middle double height (keep bias)
    sendCommand(0x72);  // ROM Selection
    sendChar(0x00);     // Select ROM A
    sendCommand(0x3C);  // FS: IS=0 RE=0, 8 bit, 4 lines, double height
    close();
}

void Display::sleep() const {
    open();
    sendCommand(0x08);  // Display Off
    sendCommand(0x3A);  // FS: IS=0 RE=1, 8 bit, 4 lines
    sendCommand(0x03);  // Power Down
    close();
}

void Display::wakeup() const {
    open();
    sendCommand(0x02);  // Power Up
    sendCommand(0x3C);  // FS: IS=0 RE=0, 8 bit, 4 lines, double height
    sendCommand(0x0C);  // Display on, Cursor off, Cursor blink off
    close();
}

void Display::print(int row, char *text) const {
    open();
    sendCommand(0x80 + row * 0x20);
    int count = 10;
    for (char* ch = text; *ch != '\0' && count > 0; ch++, count--) {
        sendChar(*ch);
    }
    while (count-- > 0) {
        sendChar(' ');
    }
    close();
}

void Display::bargraph(int row, int percent) const {
    char output[11];

    if (percent < 0) {
        percent = 0;
    }
    if (percent > 100) {
        percent = 100;
    }

    int blocks = percent / 10;

    for (int i = 0; i < 10; i++) {
        output[i] = i < blocks ? 0xD6 : ' ';
    }

    int singles = (percent / 2) % 5;
    if (singles == 1) {
        output[blocks] = 0xDA;
    } else if (singles == 2) {
        output[blocks] = 0xD9;
    } else if (singles == 3) {
        output[blocks] = 0xD8;
    } else if (singles == 4) {
        output[blocks] = 0xD7;
    }

    output[10] = '\0';
    print(row, output);
}

void Display::balance(int row, int percent) const {
    char output[11];

    if (percent < -100) {
        percent = -100;
    }
    if (percent > 100) {
        percent = 100;
    }

    for (int i = 0; i < 10; i++) {
        output[i] = ' ';
    }

    if (percent == 0) {
        output[4] = 0x10;
        output[5] = 0x11;
    } else if (percent < 0) {
        int cnt = (-percent + 9) / 10;
        for (int i = 0; i < cnt && i < 10; i++) {
            output[4 - i / 2] = (i == cnt - 1 && i % 2 == 0) ? 0x94 : 0xD0;
        }
    } else {
        int cnt = (percent + 9) / 10;
        for (int i = 0; i < cnt && i < 10; i++) {
            output[5 + i / 2] = (i == cnt - 1 && i % 2 == 0) ? 0x94 : 0xD0;
        }
    }

    output[10] = '\0';
    print(row, output);
}

void Display::open() const {
    SPI.beginTransaction(SPISettings(BITRATE, LSBFIRST, SPI_MODE3));
    digitalWrite(csPin, LOW);
}

void Display::close() const {
    digitalWrite(csPin, HIGH);
    SPI.endTransaction();
}

void Display::wait() const {
    SPI.transfer(0x3F);
    unsigned int result = SPI.transfer(0x00);
    while (result & 0x01 != 0) {
        // TODO: We need some kind of timeout...
        result = SPI.transfer(0x00);
    }
}

void Display::sendCommand(char cmd) const {
    SPI.transfer(0x1F);
    SPI.transfer(cmd & 0x0F);
    SPI.transfer((cmd >> 4) & 0x0F);
    wait();
}

void Display::sendChar(char chr) const {
    SPI.transfer(0x5F);
    SPI.transfer(chr & 0x0F);
    SPI.transfer((chr >> 4) & 0x0F);
    wait();
}
