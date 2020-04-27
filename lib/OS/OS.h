/**
 * OS structure
 */

#ifndef __OS_H__
#define __OS_H__

class OS
{
public:
    /**
     * Setup the OS
     */
    static void setup();

    /**
     * The OS main loop
     */
    static void run();
};

#endif