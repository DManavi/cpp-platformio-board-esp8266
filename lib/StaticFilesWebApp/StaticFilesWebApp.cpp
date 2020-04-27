/**
 * Static files web app
 */

#include <StaticFilesWebApp.h>

#include <Debug.h>
#include <StaticFileService.h>
#include <WebServer.h>
#include <WebShared.h>

// Allocate memory for static members
StaticFilesWebAppConfig *StaticFilesWebApp::_config = new StaticFilesWebAppConfig();

// Private

void StaticFilesWebApp::configure()
{
    Debug::l(F("I(\"StaticFilesWebApp.configure: called\")"));

    // TODO: load configuration from JSON file

    Debug::l(F("I(\"StaticFilesWebApp.configure: done\")"));
}

void StaticFilesWebApp::handle()
{
    if (!StaticFilesWebApp::_config->enabled || !StaticFileService::serve(StaticFilesWebApp::_config->root, WebServer::getWebServer()->uri().c_str()))
    {
        WebServer::sendStatus(HTTP_STATUS_NOT_FOUND);
    }
}

// Public

void StaticFilesWebApp::setup()
{
    Debug::l(F("I(\"StaticFilesWebApp.setup: called\")"));

    Debug::l(F("I(\"StaticFilesWebApp.setup: Setting default values...\")"));
    strlcpy(StaticFilesWebApp::_config->root, "/web", sizeof(StaticFilesWebApp::_config->root));

    // configure using JSON object
    StaticFilesWebApp::configure();

    // register not found route
    WebServer::getWebServer()->onNotFound(StaticFilesWebApp::handle);

    Debug::l(F("I(\"StaticFilesWebApp.setup: done\")"));
}