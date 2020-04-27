/**
 * Shared
 */

#ifndef __SHARED_H__
#define __SHARED_H__

// NOP function (No-operation)
#define nop() __asm__("nop\n\t");

/**
  * Debug message format
  * 
  * E("method_path", error_code, error_message)
  * I("method_path: error_message")
  */

/**
  * HTTP
  */

/**
  * Mime types
  */

const char HTTP_MIME_TEXT_PLAIN[] PROGMEM = "text/plain";
const char HTTP_MIME_JSON[] PROGMEM = "application/json";

/**
  * Errors
  */

const char HTTP_ERROR_NOT_FOUND[] PROGMEM = "NOT FOUND";

#endif