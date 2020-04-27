/**
 * Arduino-framework application structure
 * 
 * This file is used to be independent from the Arduino framework.
 * This is just a simple wrapper for the arduino-framework application
 * structure.
 */

#include <Arduino.h>
#include <OS.h>

void setup()
{
    // OS-specific code(s)
    OS::setup();
}

void loop()
{
    // MAIN OS LOOP
    // DO NOT RUN ANYTHING ELSE
    // Prevent using any kind of delay/wait operations
    OS::run();
}