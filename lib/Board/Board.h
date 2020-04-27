/**
 * Board
 */

#ifndef __BOARD_H__
#define __BOARD_H__

class Board
{
public:
    /**
     * Crashes the OS before starting the task scheduler
     * 
     * Note: Do not call this method during a scheduler task execution
     */
    static void halt();

    /**
     * Reboot system
     */
    static void reboot();
};

#endif