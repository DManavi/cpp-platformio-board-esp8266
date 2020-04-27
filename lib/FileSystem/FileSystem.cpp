/**
 * SPIFFS implementation
 */

#include <FileSystem.h>

#include <ArduinoJson.h>
#include <FS.h>

#include <Debug.h>
#include <Board.h>

void FileSystem::setup()
{
    Debug::l(F("I(\"FileSystem.setup: called\")"));
    delay(FileSystem::startupDelay);

    if (!SPIFFS.begin())
    {
        Debug::l(F("I(\"FileSystem.setup: SPIFFS.begin -> failed. Formatting...\")"));

        if (SPIFFS.format())
        {
            Debug::l(F("I(\"FileSystem.setup: Format successful\")"));

            Board::reboot();
            return;
        }

        Debug::l(F("I(\"FileSystem.setup: Format failed.\")"));
        Debug::l(F("E(\"FileSystem.setup\", 0x01, \"SPIFFS begin/format failed\")"));

        Board::halt();
        return;
    }

    Debug::l(F("I(\"FileSystem.setup: Done\")"));
}

bool FileSystem::fileExists(const char *filePath)
{
    return SPIFFS.exists(filePath);
}

bool FileSystem::deleteFile(const char *filePath)
{
    return SPIFFS.remove(filePath);
}

bool FileSystem::renameFile(const char *oldName, const char *newName)
{
    return SPIFFS.rename(oldName, newName);
}

void FileSystem::writeOrAppendToFile(const char *filePath, const uint8_t *buff, size_t size)
{
    String *mode = new String("w");

    if (SPIFFS.exists(filePath))
    {
        mode = new String("a");
    }

    File file = SPIFFS.open(filePath, mode->c_str());
    file.write(buff, size);
    file.close();
}

FileSystemReadJsonFileErrors FileSystem::readJsonFile(const char filePath[], const unsigned long maxFileSize, DynamicJsonDocument *doc)
{
    Debug::l(F("I(\"FileSystem.readJsonFile: called\")"));

    // 1) Check file existence

    Debug::w(F("I(\"FileSystem.readJsonFile: Check existence: "));
    Debug::w(filePath);
    Debug::l(F("\")"));

    if (!SPIFFS.exists(filePath))
    {
        Debug::w(F("E(\"FileSystem.readJsonFile\", "));
        Debug::w(String((uint8_t)FileSystemReadJsonFileErrors::FILE_NOT_FOUND, DEC));
        Debug::l(F(", \"Not exists\")"));
        return FileSystemReadJsonFileErrors::FILE_NOT_FOUND;
    }
    Debug::l(F("I(\"FileSystem.readJsonFile: File exists\")"));

    // 2) Open file stream

    Debug::l(F("I(\"FileSystem.readJsonFile: Opening file...\")"));
    File file = SPIFFS.open(filePath, "r");

    if (!file)
    {
        Debug::w(F("E(\"FileSystem.readJsonFile\", "));
        Debug::w(String((uint8_t)FileSystemReadJsonFileErrors::READ_FAILED, DEC));
        Debug::l(F(", \"Read failed\")"));
        return FileSystemReadJsonFileErrors::READ_FAILED;
    }
    Debug::l(F("I(\"config.load: File OK\")"));

    // 3) Check file size
    Debug::w(F("I(\"FileSystem.readJsonFile: Checking file size. Max: "));
    Debug::w(String(maxFileSize, DEC));
    Debug::l(F("\")"));

    size_t fileSize = file.size();

    Debug::w(F("I(\"FileSystem.readJsonFile: Checking file size. Actual: "));
    Debug::w(String(fileSize, DEC));
    Debug::l(F("\")"));

    if (fileSize > maxFileSize)
    {
        Debug::w(F("E(\"FileSystem.readJsonFile\", "));
        Debug::w(String((uint8_t)FileSystemReadJsonFileErrors::LARGE_FILE, DEC));
        Debug::l(F(", \"Large file\")"));
        return FileSystemReadJsonFileErrors::LARGE_FILE;
    }
    Debug::l(F("I(\"FileSystem.readJsonFile: File size OK\")"));

    // 4) Deserialize JSON
    DeserializationError error = deserializeJson(*doc, file);

    if (error)
    {
        Debug::w(F("E(\"FileSystem.readJsonFile\", "));
        Debug::w(String((uint8_t)FileSystemReadJsonFileErrors::INVALID_JSON, DEC));
        Debug::w(error.c_str());
        Debug::l(F(", \"Invalid JSON\")"));
        return FileSystemReadJsonFileErrors::INVALID_JSON;
    }

    return FileSystemReadJsonFileErrors::OK;
}