/**
 * Shared configuration
 */

#ifndef __SHARED_CONFIG_H__
#define __SHARED_CONFIG_H__

#include <ESP8266WiFi.h>

struct IPConfig
{
    IPAddress address;
    IPAddress subnet;
    IPAddress gateway;
    IPAddress DNS1;
    IPAddress DNS2;

    bool DHCP = true;
    bool configured = false;
};

struct WiFiNetworkBasicConfig
{
    char SSID[31];
    char passphrase[63];
};

#endif