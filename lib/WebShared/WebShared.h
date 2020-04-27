/**
 * Web shared header
 */

#ifndef __WEB_SHARED_H__
#define __WEB_SHARED_H__

#include <ArduinoJson.h>

const uint16_t HTTP_DEFAULT_PORT PROGMEM = 80;

const uint16_t HTTP_STATUS_OK PROGMEM = 200;
const uint16_t HTTP_STATUS_ACCEPTED PROGMEM = 202;

const uint16_t HTTP_STATUS_BAD_REQUEST PROGMEM = 400;
const uint16_t HTTP_STATUS_NOT_FOUND PROGMEM = 404;
const uint16_t HTTP_STATUS_NOT_ACCEPTABLE PROGMEM = 406;
const uint16_t HTTP_STATUS_CONFLICT = 409;
const uint16_t HTTP_STATUS_TOO_MANY_REQUESTS PROGMEM = 429;

const uint16_t HTTP_STATUS_SERVER_ERROR = 500;

const char HTTP_MIME_APPLICATION_JSON[] PROGMEM = "application/json";
const char HTTP_MIME_TEXT_PLAIN[] PROGMEM = "text/plain";

// const char ROUTE_API_DEVICE_CONFIG_SERVICE[] PROGMEM = "/api/device-config";

#endif