/**
 * WiFi Module
 */

#include <WiFiModule.h>
#include <ESP8266WiFi.h>
#include <Debug.h>

void WiFiModule::setup()
{
    Debug::l(F("I(\"WiFiModule.setup: called\")"));

    // wait for WiFi module
    delay(WiFiModule::startupDelay);

    // enable both AP & Station module
    WiFi.mode(WIFI_AP_STA);

    // Disable WiFi AP
    WiFi.softAPdisconnect(true);

    // Decide which mode/modes to be initialized
    WiFi.persistent(false);
    WiFi.setAutoConnect(false);
    WiFi.setAutoReconnect(true);
    WiFi.disconnect(true);

    Debug::l(F("I(\"WiFiModule.setup: Done\")"));
}