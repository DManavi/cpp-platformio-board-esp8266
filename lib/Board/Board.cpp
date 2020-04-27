/**
 * Board
 */

#include <Board.h>
#include <Arduino.h>
#include <Debug.h>

/**
 * Crashes the OS before starting the task scheduler
 * 
 * Note: Do not call this method during a scheduler task execution
 */
void Board::halt()
{
    Debug::l(F("I(\"Board.halt: called\")"));

    while (true)
    {
        Debug::l(F("I(\"Board.halt: live\")"));

        delay(3000);
    };
}

/**
 * Reboot system
 */
void Board::reboot()
{
    Debug::l(F("I(\"Board.reboot: called\")"));
    ESP.restart();
}