/**
 * WiFi module
 */

#ifndef __WiFi_Module_h__
#define __WiFi_Module_h__

#include <Arduino.h>

class WiFiModule
{
private:
    static const uint8_t startupDelay = 150;

public:
    static void setup();
};

#endif