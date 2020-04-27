/**
 * Static file service
 */

#ifndef __STATIC_FILE_SERVICE_H__
#define __STATIC_FILE_SERVICE_H__

#include <Arduino.h>

struct StaticFileServiceOptions
{
    bool GZEnabled = true;
    bool download = false;
    bool addIndexToDir = true;
};

struct StaticFileServiceFallbackOptions
{
    bool enabled = false;
    const char *fileName;
};

struct StaticFileExistenceResult
{
    bool original = false;
    bool GZ = false;
    bool fallback = false;
};

class StaticFileService
{
private:
    static void addIndexToDir(String *path);
    static String getMimeTypeByExtension(String *path, bool download);

    static StaticFileExistenceResult fileExists(const char *root, String *path, bool checkGZ, StaticFileServiceFallbackOptions *fallback);

public:
    static bool serve(const char *root, const char *uri);
    static bool serve(const char *root, const char *uri, StaticFileServiceOptions *options);
    static bool serve(const char *root, const char *uri, StaticFileServiceOptions *options, StaticFileServiceFallbackOptions *fallback);
};

#endif