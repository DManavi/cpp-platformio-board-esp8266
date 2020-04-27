/**
 * Serial Debug
 */

#include <Debug.h>

void Debug::setup()
{
    delay(Debug::startupDelay);

    Serial.setDebugOutput(false);
    Serial.begin(Debug::baudrate);
}

void Debug::w(const __FlashStringHelper *ifsh)
{
    if (Debug::enabled)
    {
        Serial.print(ifsh);
    }
}

void Debug::w(const String &s)
{
    if (Debug::enabled)
    {
        Serial.print(s);
    }
}

void Debug::l(const __FlashStringHelper *ifsh)
{
    if (Debug::enabled)
    {
        Serial.println(ifsh);
    }
}

void Debug::l(const String &s)
{
    if (Debug::enabled)
    {
        Serial.println(s);
    }
}