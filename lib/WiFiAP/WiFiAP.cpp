/**
 * WiFi AP
 */

#include <WiFiAP.h>

#include <ESP8266WiFi.h>

#include <Board.h>
#include <Debug.h>

// Allocate memory for static members
WiFiAPConfig *WiFiAP::_config = new WiFiAPConfig();

// Private

void WiFiAP::configure()
{
    Debug::l(F("I(\"WiFiAP.configure: called\")"));

    // TODO: load configuration from JSON file

    Debug::l(F("I(\"WiFiAP.configure: Done\")"));
}

// Public

void WiFiAP::setup()
{
    Debug::l(F("I(\"WiFiAP.setup: called.\")"));

    Debug::l(F("I(\"WiFiAP.setup: Setting default configuration...\")"));
    strlcpy(WiFiAP::_config->network->SSID, "NECK-", sizeof(WiFiAP::_config->network->SSID));
    strlcpy(WiFiAP::_config->network->passphrase, "", sizeof(WiFiAP::_config->network->passphrase));

    WiFiAP::_config->IP->address.fromString(F("10.10.0.1"));
    WiFiAP::_config->IP->subnet.fromString(F("255.255.255.0"));
    WiFiAP::_config->IP->gateway.fromString(F("0.0.0.0"));

    WiFiAP::_config->IP->DNS1.fromString(F("0.0.0.0"));
    WiFiAP::_config->IP->DNS2.fromString(F("0.0.0.0"));

    WiFiAP::_config->IP->DHCP = false;

    // configure using JSON object
    WiFiAP::configure();

    WiFiAPConfig *config = WiFiAP::_config;

    if (config->enabled)
    {
        Debug::l(F("I(\"WiFiAP.setup: Enabled\")"));

        if (config->network->addMACToSSID)
        {
            Debug::l(F("I(\"WiFiAP.setup: Adding MAC address to the SSID...\")"));

            // skip 3 first bytes (11:22:33:44:55:66) -> 44:55:66
            String macPart = WiFi.softAPmacAddress().substring(9);
            uint8_t macPointer = strlen(config->network->SSID) - 1;

            for (uint8_t i = 0; i < macPart.length(); i++)
            {
                config->network->SSID[++macPointer] = macPart[i];

                if (strlen(config->network->SSID) == sizeof(config->network->SSID))
                {
                    break;
                }
            }

            Debug::w(F("I(\"WiFiAP.setup: New SSID: "));
            Debug::w(config->network->SSID);
            Debug::l(F("\")"));

        } // end of config->network->addMACToSSID

        Debug::l(F("I(\"WiFiAP.setup: Applying IP configuration...\")"));
        if (!WiFi.softAPConfig(config->IP->address, config->IP->gateway, config->IP->subnet))
        {
            Debug::l(F("E(\"WiFiAP.setup\", 0x01, \"IP config failed\")"));
            return Board::halt();
        }

        // set IP configured flag
        config->IP->configured = true;

        Debug::l(F("I(\"WiFiAP.setup: Starting AP...\")"));
        if (!WiFi.softAP(config->network->SSID, config->network->passphrase, config->network->channel, config->network->hidden, config->network->maxClients))
        {
            Debug::l(F("E(\"WiFiAP.setup\", 0x02, \"AP start failed\")"));
            return Board::halt();
        }

    } // end of config->enabled
    else
    {
        Debug::l(F("I(\"WiFiAP.setup: Disabled\")"));
    }

    Debug::l(F("I(\"WiFiAP.setup: Done\")"));
}