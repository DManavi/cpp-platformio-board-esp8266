/**
 * OS implementation
 */

#include <OS.h>
#include <TaskScheduler.h>

#include <Debug.h>
#include <DeviceConfig.h>
#include <FileSystem.h>
#include <StaticFilesWebApp.h>
#include <WebServer.h>
#include <WiFiAP.h>
#include <WiFiModule.h>

Scheduler scheduler;

Task webServerHandleClientTask(15, TASK_FOREVER, &WebServer::handleClientCallback, &scheduler, false);

void OS::setup()
{
    // Prepare basic IO (Terminal/Serial, File system, and etc)
    Debug::setup();
    WiFiModule::setup();
    FileSystem::setup();

    // Initialize application-level configuration
    // load either defaults or config file.
    DeviceConfig::setup();

    // Prepare WiFi connectivity components
    WiFiAP::setup();

    // Prepare network servers
    WebServer::setup();

    // Prepare web application(s)
    StaticFilesWebApp::setup(); // This one must be the last web application that is initialized

    // Start network servers
    WebServer::start();                 // HTTP web server

    // Manage (Enable/Disable) OS tasks
    webServerHandleClientTask.enableIfNot();
}

void OS::run()
{
    // execute all the tasks
    scheduler.execute();
}