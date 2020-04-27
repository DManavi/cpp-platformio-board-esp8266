/**
 * WiFi AP
 */

#ifndef __WIFI_AP_H__
#define __WIFI_AP_H__

#include <SharedConfig.h>

struct WiFiNetworkConfig
{
    char SSID[31];
    char passphrase[63];
    bool hidden = false;
    byte channel = 13;
    byte maxClients = 8;

    bool addMACToSSID = true;
};

struct WiFiAPConfig
{
    WiFiNetworkConfig *network;
    IPConfig *IP;
    bool enabled = true;

    WiFiAPConfig()
    {
        this->network = new WiFiNetworkConfig();
        this->IP = new IPConfig();
    }
};

class WiFiAP
{
private:
    static WiFiAPConfig *_config;

    static void configure();

public:
    static void setup();
};

#endif