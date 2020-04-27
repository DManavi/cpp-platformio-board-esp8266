/**
 * Static file service
 */

#include <StaticFileService.h>

#include <Arduino.h>
#include <FS.h>

#include <Debug.h>
#include <WebServer.h>

// Private methods

void StaticFileService::addIndexToDir(String *path)
{
    if (path->endsWith(F("/")))
    {
        path->concat(F("index.html"));
    }
}

StaticFileExistenceResult StaticFileService::fileExists(const char *root, String *path, bool checkGZ, StaticFileServiceFallbackOptions *fallback)
{
    StaticFileExistenceResult result = StaticFileExistenceResult();

    String *absolutePath = new String(root);
    absolutePath->concat(path->c_str());

    Debug::w(F("I(\"StaticFileService.fileExists: absolutePath: "));
    Debug::w(absolutePath->c_str());
    Debug::l(F("\")"));

    // original file existence
    result.original = SPIFFS.exists(absolutePath->c_str());

    // GZ file existence
    if (checkGZ)
    {
        String *gzPath = new String(absolutePath->c_str());
        gzPath->concat(F(".gz"));

        Debug::w(F("I(\"StaticFileService.fileExists: gzPath: "));
        Debug::w(gzPath->c_str());
        Debug::l(F("\")"));

        result.GZ = SPIFFS.exists(gzPath->c_str());
    }

    // fallback file support
    if (fallback->enabled)
    {
        String *fallbackPath = new String(root);
        fallbackPath->concat("/");
        fallbackPath->concat(fallback->fileName);

        Debug::w(F("I(\"StaticFileService.fileExists: fallbackPath: "));
        Debug::w(fallbackPath->c_str());
        Debug::l(F("\")"));

        result.fallback = SPIFFS.exists(fallbackPath->c_str());
    }

    return result;
}

String StaticFileService::getMimeTypeByExtension(String *path, bool download)
{
    if (download)
    {
        return String(F("application/octet-stream"));
    }
    else if (path->endsWith(F(".htm")))
    {
        return String(F("text/html"));
    }
    else if (path->endsWith(F(".html")))
    {
        return String(F("text/html"));
    }
    else if (path->endsWith(F(".css")))
    {
        return String(F("text/css"));
    }
    else if (path->endsWith(F(".js")))
    {
        return String(F("application/javascript"));
    }
    else if (path->endsWith(F(".png")))
    {
        return String(F("image/png"));
    }
    else if (path->endsWith(F(".gif")))
    {
        return String(F("image/gif"));
    }
    else if (path->endsWith(F(".jpg")))
    {
        return String(F("image/jpeg"));
    }
    else if (path->endsWith(F(".ico")))
    {
        return String(F("image/x-icon"));
    }
    else if (path->endsWith(F(".xml")))
    {
        return String(F("text/xml"));
    }
    else if (path->endsWith(F(".pdf")))
    {
        return String(F("application/x-pdf"));
    }
    else if (path->endsWith(F(".zip")))
    {
        return String(F("application/x-zip"));
    }
    else if (path->endsWith(F(".gz")))
    {
        return String(F("application/x-gzip"));
    }

    return String(F("text/plain"));
}

// Public methods

bool StaticFileService::serve(const char *root, const char *uri)
{
    StaticFileServiceOptions *options = new StaticFileServiceOptions();

    return StaticFileService::serve(root, uri, options);
}

bool StaticFileService::serve(const char *root, const char *uri, StaticFileServiceOptions *options)
{
    StaticFileServiceFallbackOptions *fallback = new StaticFileServiceFallbackOptions();

    return StaticFileService::serve(root, uri, options, fallback);
}

bool StaticFileService::serve(const char *root, const char *uri, StaticFileServiceOptions *options, StaticFileServiceFallbackOptions *fallback)
{
    Debug::l(F("I(\"StaticFileService.serve: called\")"));

    // convert URI to string
    String *path = new String(uri);

    // if URI is a directory or root folder, add index.html
    if (options->addIndexToDir)
    {
        Debug::l(F("I(\"StaticFileServer.serve: Adding index to directory\")"));

        StaticFileService::addIndexToDir(path);
    }

    Debug::w(F("I(\"StaticFileService.serve: Path: "));
    Debug::w(path->c_str());
    Debug::l(F("\")"));

    Debug::l(F("I(\"StaticFileServer.serve: Checking file existence...\")"));

    // check file existence
    StaticFileExistenceResult existence = StaticFileService::fileExists(root, path, options->GZEnabled, fallback);

    Debug::w(F("I(\"StaticFileServer.serve: Existence result: "));
    Debug::w("Original: ");
    Debug::w(existence.original ? F("True") : F("False"));
    Debug::w(", Fallback: ");
    Debug::w(existence.fallback ? F("True") : F("False"));
    Debug::w(", GZ: ");
    Debug::w(existence.GZ ? F("True") : F("False"));
    Debug::l(F("\")"));

    Debug::w(F("I(\"StaticFileServer.serve: Path: "));
    Debug::w(path->c_str());
    Debug::l(F("\")"));

    // neither original nor GZ exists
    if (!existence.original && !existence.GZ)
    {
        // no fallback requested
        if (!fallback->enabled)
        {
            Debug::l(F("I(\"StaticFileServer.serve: No valid file exists\")"));
            return false;
        }

        // fallback file not found
        if (!existence.fallback)
        {
            Debug::l(F("I(\"StaticFileServer.serve: Fallback file not found\")"));
            return false;
        }

        Debug::l(F("I(\"StaticFileServer.serve: Changing file name to fallback one...\")"));

        // replace path with the fallback file path
        path = new String(root);
        path->concat("/");
        path->concat(fallback->fileName);
    }

    // GZ file allowed and exists
    if (options->GZEnabled && existence.GZ)
    {
        Debug::l(F("I(\"StaticFileServer.serve: Adding GZ extension...\")"));

        // add .gz extension
        path->concat(".gz");
    }

    ESP8266WebServer *webServer = WebServer::getWebServer();
    String contentType = StaticFileService::getMimeTypeByExtension(path, options->download);

    String *absoluteFilePath = new String(root);
    absoluteFilePath->concat(path->c_str());

    Debug::w(F("I(\"StaticFileServer.serve: Absolute Path: "));
    Debug::w(absoluteFilePath->c_str());
    Debug::l(F("\")"));

    File file = SPIFFS.open(absoluteFilePath->c_str(), "r");
    webServer->streamFile(file, contentType);
    file.close();

    return true;
}