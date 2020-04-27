/**
 * Device config
 */

#ifndef __DEVICE_CONFIG_H__
#define __DEVICE_CONFIG_H__

#include <Arduino.h>
#include <ArduinoJson.h>

class DeviceConfig
{
private:
    static bool configFileExists;
    static DynamicJsonDocument *_config;

    static void loadConfigFile();

public:
    static void setup();

    static JsonObject get(const char *moduleName);
};

#endif