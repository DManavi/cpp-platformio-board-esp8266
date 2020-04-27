/**
 * Debug library
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <Arduino.h>

class Debug
{
private:
    static const byte startupDelay = 50;
    static const unsigned int baudrate = 115200;
    static const bool enabled = true;

public:
    static void setup(); // setup Serial Debug

    static void w(const __FlashStringHelper *ifsh);
    static void w(const String &s);

    static void l(const __FlashStringHelper *ifsh);
    static void l(const String &s);
};

#endif