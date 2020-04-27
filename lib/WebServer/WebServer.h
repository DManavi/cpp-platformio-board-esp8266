/**
 * Web server
 */

#ifndef __WEB_SERVER_H__
#define __WEB_SERVER_H__

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

struct WebServerConfig
{
    uint16_t port = 80;
};

class WebServer
{
private:
    static ESP8266WebServer *_webServer;
    static WebServerConfig *_config;

    static void configure();

public:
    static void setup();
    static void start();

    static void sendStatus(uint16_t status);
    static void sendStatus(uint16_t status, const char *mimeType);
    static void sendJson(uint16_t status, JsonDocument doc);

    static void handleClientCallback();

    static ESP8266WebServer *getWebServer();
};

#endif