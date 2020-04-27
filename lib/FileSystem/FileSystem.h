/**
 * File system helpers
 */

#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <ArduinoJson.h>

enum class FileSystemReadJsonFileErrors
{
    OK = 0x00,
    FILE_NOT_FOUND = 0x01,
    READ_FAILED = 0x02,
    LARGE_FILE = 0x03,
    INVALID_JSON = 0x04
};

class FileSystem
{
private:
    static const uint8_t startupDelay = 150;

public:
    static void setup();

    static bool fileExists(const char *filePath);
    static bool deleteFile(const char *filePath);
    static bool renameFile(const char *oldName, const char *newName);

    static void writeOrAppendToFile(const char *filePath, const uint8_t *buff, size_t size);

    static FileSystemReadJsonFileErrors readJsonFile(const char filePath[], const unsigned long maxFileSize, DynamicJsonDocument *doc);
};

#endif