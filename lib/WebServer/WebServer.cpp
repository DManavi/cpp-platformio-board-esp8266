/**
 * Web Server
 */

#include <WebServer.h>

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include <Debug.h>
#include <WebShared.h>

// Allocate memory for static members

ESP8266WebServer *WebServer::_webServer = new ESP8266WebServer();
WebServerConfig *WebServer::_config = new WebServerConfig();

// Private

void WebServer::configure()
{
    Debug::l(F("I(\"WebServer.configure: called\")"));

    // TODO: load configuration from JSON file

    Debug::l(F("I(\"WebServer.configure: done\")"));
}

// Public

void WebServer::setup()
{
    Debug::l(F("I(\"WebServer.setup: called\")"));

    Debug::l(F("I(\"WebServer.setup: Setting default config...\")"));

    // configure using JSON object
    WebServer::configure();

    Debug::l(F("I(\"WebServer.setup: Done\")"));
}

void WebServer::start()
{
    Debug::l(F("I(\"WebServer.start: called\")"));

    // start listening on the specified port number
    WebServer::_webServer->begin(WebServer::_config->port);

    Debug::l(F("I(\"WebServer.start: Done\")"));
}

void WebServer::sendStatus(uint16_t status)
{
    WebServer::_webServer->send(status);
}

void WebServer::sendStatus(uint16_t status, const char *mimeType)
{
    WebServer::_webServer->send(status, mimeType);
}

void WebServer::sendJson(uint16_t status, JsonDocument doc)
{
    String buff;

    serializeJson(doc, buff);

    WebServer::_webServer->send(status, HTTP_MIME_APPLICATION_JSON, buff);
}

// read-only getters

ESP8266WebServer *WebServer::getWebServer()
{
    return WebServer::_webServer;
}

// OS tasks

/**
 * OS task
 * Use neither synchornous code nor delay function
 */
void WebServer::handleClientCallback()
{
    WebServer::_webServer->handleClient();
}