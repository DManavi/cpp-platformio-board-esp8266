/**
 * Static files web application
 */

#ifndef __STATIC_FILES_WEB_APP_H__
#define __STATIC_FILES_WEB_APP_H__

struct StaticFilesWebAppConfig
{
    char root[16];
    bool enabled = true;
};

class StaticFilesWebApp
{
private:
    static StaticFilesWebAppConfig *_config;

    static void configure();
    static void handle();

public:
    static void setup();
};

#endif